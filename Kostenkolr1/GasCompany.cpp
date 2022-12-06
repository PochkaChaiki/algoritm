#include "GasCompany.h"
#include <iostream>

bool GasCompany::IsCSFree(int CSID){
    for (auto& node: Connections)
        if ((node.second.ExitID == CSID) || (node.second.EnterID == CSID))
            return false;

    return true;
}

int GasCompany::GetCSdegree(int CSID){
    int degree(0);
    for (auto& node: Connections)
        if ((node.second.EnterID == CSID) || (node.second.ExitID == CSID))
            degree++;
        
    return degree;
}

void GasCompany::addCS(){
    CompressorStation CS;
    std::cin >> CS;
    StationsGroup.insert({CS.GetID(), CS});
    std::cout << "Id currently used compressor station: " << CS.GetID() << "\n\n";
    
}

void GasCompany::addConnection(){
    Pipe pipe;
    Graph::Edge newEdge;
    newEdge.EdgeID = pipe.GetID();

    std::cout << "Enter start compressor station: ";
    newEdge.EnterID = GetRightValue(std::cin, 0, CompressorStation::ID_counter - 1);
    while ((StationsGroup.find(newEdge.EnterID) == StationsGroup.end()) || (GetCSdegree(newEdge.EnterID) >= StationsGroup[newEdge.EnterID].GetShopsAmount())){
        std::cout << "Input error: Invalid choice of compressor station. Type \"0\" to stop or Try Again.\n";
        newEdge.EnterID = GetRightValue(std::cin, 0, CompressorStation::ID_counter - 1);
        if (newEdge.EnterID == 0){
            return;
        }
    }
    
    std::cout << "Enter end compressor station: ";
    newEdge.ExitID = GetRightValue(std::cin, 0, CompressorStation::ID_counter - 1);
    while ((StationsGroup.find(newEdge.ExitID) == StationsGroup.end()) || (GetCSdegree(newEdge.ExitID) >= StationsGroup[newEdge.ExitID].GetShopsAmount()) || (newEdge.ExitID == newEdge.EnterID)){
        std::cout << "Input error: Invalid choice of compressor station. Type \"0\" to stop or Try Again.\n";
        newEdge.ExitID = GetRightValue(std::cin, 0, CompressorStation::ID_counter - 1);
        if (newEdge.ExitID == 0){
            return;
        }
    }
    
    Connections.insert({newEdge.EdgeID, newEdge});
    std::cin >> pipe;
    Pipeline.insert({pipe.GetID(), pipe});
    std::cout << "Id currently used pipe: " << pipe.GetID() << "\n\n";
}

void GasCompany::editPipes(){
    if (Pipeline.size() == 0){
        std::cout<<"EDIT ERROR: There're no pipes in your pipeline. Add one and try again."<<std::endl;
        return;
    }
    std::unordered_set<int> searchResultSet;
    getObjectsToEdit(Pipeline, searchResultSet);
    int actionChoice;
    std::cout<<"Select an action for the pipe (-s) (\"0\" - to edit the pipe (-s), \"1\" - to delete the pipe (-s)): "<<std::endl;
    actionChoice = GetRightValue(std::cin, 0, 1);
    if (actionChoice == 0){
        std::cout << "Enter status to set to pipes: ";
        int statusToSet = GetRightValue(std::cin, 0, 1);
        for (auto id: searchResultSet)
            Pipeline[id].SetStatus(statusToSet);
        }
    else if (actionChoice == 1)
        for (auto id: searchResultSet){
            Connections.erase(Connections.find(id));
            Pipeline.erase(Pipeline.find(id)); 
        }
}

void GasCompany::editCompressorStations(){
    if (StationsGroup.size() == 0){
        std::cout<<"EDIT ERROR: There're no compressor stations in your stations list. Add one and try again."<<std::endl;
        return;
    } 
    
    std::unordered_set<int> searchResultSet;
    getObjectsToEdit(StationsGroup, searchResultSet);

    int actionChoice;
    std::cout << "Select an action for the station (-s) (\"0\" - to edit the station (-s), \"1\" - to delete the station (-s)): " << std::endl;
    actionChoice = GetRightValue(std::cin, 0, 1);
    if (actionChoice == 0){
        for (auto id: searchResultSet)
            StationsGroup[id].EditCompressorStation();
    }
    else if (actionChoice == 1)
        for (auto& id: searchResultSet){
            if (!IsCSFree(id)){
                std::cout << "Deleting is denied. Unlink pipes from compressor station first.\n";
                continue;
            } else {
                StationsGroup.erase(StationsGroup.find(id));
            }
        }
}

void GasCompany::findObjects(){
    std::unordered_set<int> searchResult;
    int choiceObject;

    std::cout<<"Choose object to use filter search on (type \"0\" for pipes or \"1\" for compressor stations): ";
    choiceObject = GetRightValue(std::cin, 0, 1);
    if (choiceObject == 0){
        searchObjects(Pipeline, searchResult);
        if (searchResult.size() != 0)
            for (auto obj: searchResult)
                std::cout<<Pipeline[obj]<<std::endl;
        else
            std::cout << "Pipes weren't found." << std::endl;
    } else if (choiceObject == 1){
        searchObjects(StationsGroup, searchResult);
        if (searchResult.size() != 0)
            for (auto obj: searchResult)
                std::cout<<StationsGroup[obj]<<std::endl;
        else
            std::cout << "Compressor stations weren't found." << std::endl;
    }
}

void GasCompany::showObjects(){
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto pipe : Pipeline){
        std::cout << pipe.second;
        std::cout << "Pipe connects compressor stations: \n\t" << Connections[pipe.first].EnterID << " --> " << Connections[pipe.first].ExitID << std::endl;
        std::cout << "\n=...=...=...=...=...=...=...=...=...=...=...=...=...=...=\n";
    }
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto station: StationsGroup){
        std::cout << station.second;
        std::cout << "\n\tPlugged to cs pipes: ";
        for (auto& link: Connections)
            if ((link.second.EnterID == station.second.GetID()) || (link.second.ExitID == station.second.GetID()))
                std::cout << link.first << " ";
        std::cout << "\n=...=...=...=...=...=...=...=...=...=...=...=...=...=...=\n";
    }
}

void GasCompany::saveCompany(std::string filename){
    std::ofstream fout(filename, std::ios::out);
    if (fout){
        fout << "Pipes: " << Pipeline.size() << ",";
        for (auto pipe: Pipeline)
            fout << pipe.second << Connections[pipe.first].EnterID << "," << Connections[pipe.first].ExitID << ",";

        fout << "Stations: " << StationsGroup.size() << ",";
        for (auto station: StationsGroup)
            fout << station.second;

        fout.close();
    } else {
        std::cout<<"WRITE ERROR: Failed to open file."<<std::endl;
    }
}

void GasCompany::loadCompany(std::string filename){
    std::ifstream fin(filename, std::ios::in);
    if (fin){
        Pipe::ID_counter = 0;
        CompressorStation::ID_counter = 0;
        Pipeline.clear();
        StationsGroup.clear();
        std::string input;
        int amount;
        while(!fin.eof()){
            std::getline(fin, input, ' ');
            valueInput(fin, amount, ',');
            if (input == "Pipes:"){
                for (int i(0); i<amount; ++i){
                    Pipe pipe;
                    Graph::Edge e;
                    fin >> pipe;
                    fin >> e;
                    e.EdgeID = pipe.GetID();
                    if (fin.fail()){
                        std::cout<<"FILE READ ERROR: Failed to read pipe's parameters due to file's damage."<<std::endl;
                        continue;
                    } else {
                        Connections.insert({e.EdgeID, e});
                        Pipeline.insert({pipe.GetID(), pipe});
                    }
                    Pipe::ID_counter = ((Pipe::ID_counter < pipe.GetID())? pipe.GetID() : Pipe::ID_counter);
                }
            } else if (input == "Stations:"){
                for (int j(0); j<amount; ++j){
                    CompressorStation CS;
                    fin >> CS;
                    if (fin.fail()){
                        std::cout<<"FILE READ ERROR: Failed to read compressor station's parameters due to file's damage."<<std::endl;
                        continue;
                    } else
                        StationsGroup.insert({CS.GetID(), CS});
                    CompressorStation::ID_counter = ((CompressorStation::ID_counter < CS.GetID())? CS.GetID() : CompressorStation::ID_counter);
                }
                std::getline(fin, input, '\n');
            } else {
                std::cout<<"READ ERROR: Failed to read file. File is damaged."<<std::endl;
                fin.clear();
                fin.ignore(INT_MAX, '\n');
                fin.close();
            }
        }
    } else {
        std::cout<<"READ ERROR: Failed to open file."<<std::endl;
    }
}

void chooseIdentifiers(std::unordered_set<int>& idSet){
    std::unordered_set<int> userIdentifiers;
    int objectsAmount;
    std::cout<<"Enter amount of objects you want to edit: ";
    objectsAmount = GetRightValue(std::cin, 0, (int)idSet.size());

    std::cout<<"Enter pipes' identifiers: ";
    for (int i(0); i < objectsAmount; ++i){
        int ID = GetRightValue(std::cin, 0, INT_MAX);
        while (idSet.find(ID) == idSet.end()){
            std::cout << "EDIT ERROR: Input error. Try again." << std::endl;
            ID = GetRightValue(std::cin, 0, INT_MAX);
        }
        userIdentifiers.insert(ID);
    }
    idSet = userIdentifiers;
}

// void GasCompany::disconnect(){
//     int EdgeID;

//     std::cout << "Input pipe's id: \n";
//     EdgeID = GetRightValue(std::cin, 0, Pipe::ID_counter - 1);
//     while (Pipeline.find(EdgeID) == Pipeline.end()){
//         std::cout << "Input error: Invalid choice of pipe. Try Again.\n";
//         EdgeID = GetRightValue(std::cin, 0, Pipe::ID_counter - 1);
//     }

//     Connections.erase(Connections.find(EdgeID));
//     Pipeline.erase(Pipeline.find(EdgeID));
// }

void GasCompany::Sort(){
    std::cout << "Topological sort of graph: " << std::endl;
    Graph Network;
    Network.FillAdjecencyList(Connections);
    Network.Sort();
}