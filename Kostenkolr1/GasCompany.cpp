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

void GasCompany::editPipeline(){
    if (Pipeline.size() == 0){
        std::cout<<"EDIT ERROR: There're no Pipeline in your pipeline. Add one and try again."<<std::endl;
        return;
    }
    std::unordered_set<int> searchResultSet;
    getObjectsToEdit(Pipeline, searchResultSet);
    int actionChoice;
    std::cout<<"Select an action for the pipe (-s) (\"0\" - to edit the pipe (-s), \"1\" - to delete the pipe (-s)): "<<std::endl;
    actionChoice = GetRightValue(std::cin, 0, 1);
    if (actionChoice == 0){
        std::cout << "Enter status to set to Pipeline: ";
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
                std::cout << "Deleting is denied. Unlink Pipeline from compressor station first.\n";
                continue;
            } else {
                StationsGroup.erase(StationsGroup.find(id));
            }
        }
}

void GasCompany::findObjects(){
    std::unordered_set<int> searchResult;
    int choiceObject;

    std::cout<<"Choose object to use filter search on (type \"0\" for Pipeline or \"1\" for compressor stations): ";
    choiceObject = GetRightValue(std::cin, 0, 1);
    if (choiceObject == 0){
        searchObjects(Pipeline, searchResult);
        if (searchResult.size() != 0)
            for (auto obj: searchResult)
                std::cout<<Pipeline[obj]<<std::endl;
        else
            std::cout << "Pipeline weren't found." << std::endl;
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
        std::cout << "\n\tPlugged to cs Pipeline: ";
        for (auto& link: Connections)
            if ((link.second.EnterID == station.second.GetID()) || (link.second.ExitID == station.second.GetID()))
                std::cout << link.first << " ";
        std::cout << "\n=...=...=...=...=...=...=...=...=...=...=...=...=...=...=\n";
    }
}

void GasCompany::saveCompany(std::string filename){
    std::ofstream fout(filename, std::ios::out);
    if (fout){
        fout << "Pipeline: " << Pipeline.size() << ",";
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

    std::cout<<"Enter Pipeline' identifiers: ";
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

void GasCompany::Sort(){
    std::cout << "Topological sort of graph: " << std::endl;
    Graph Network;
    Network.FillAdjecencyList(Connections);
    Network.Sort();
}

void GasCompany::ShortestPath() {

	std::unordered_map<int, int> id_idx;
	std::unordered_map<int, int> idx_id;
	std::unordered_set<int> spt_StationsGroup;

	std::vector<std::vector<double>> graph(StationsGroup.size(), std::vector<double>(StationsGroup.size(), 0.0));

	int idx = 0;

	for (auto& [pipeID, edge] : Connections) {
		if (spt_StationsGroup.find(edge.EnterID) == spt_StationsGroup.end()) {
			id_idx[edge.EnterID] = idx;
			idx_id[idx] = edge.EnterID;
			spt_StationsGroup.insert(edge.EnterID);

			idx++;
		}

		if (spt_StationsGroup.find(edge.ExitID) == spt_StationsGroup.end()) {
			id_idx[edge.ExitID] = idx;
			idx_id[idx] = edge.ExitID;
			spt_StationsGroup.insert(edge.ExitID);

			idx++;
		}
	}

	for (auto& [pipeID, edge] : Connections) {
		if (Pipeline[pipeID].GetStatus() == 1)
			graph[id_idx[edge.EnterID]][id_idx[edge.ExitID]] = Pipeline[pipeID].GetLength();
	}

	int src;

	while (true) {
		std::cout << "Input start node: ";
		src = GetRightValue(std::cin, 1, INT_MAX);
		if (id_idx.find(src) != id_idx.end()) {
			src = id_idx[src];
			break;
		}
		std::cout << "There is no this node in graph" << std::endl;
	}

	std::vector<double> dist = Dijkstra(graph, src);

	for (int i(0); i < dist.size(); ++i) {
		std::cout << "Distance to node " << idx_id[i];
		if (dist[i] == __DBL_MAX__)
			 std::cout << " is Inf" << std::endl;
		else
			std::cout << " is " << dist[i] << std::endl;
	}
}


void GasCompany::GetMaxFlow() {
	std::unordered_map<int, int> id_idx;
	std::unordered_map<int, int> idx_id;
	std::unordered_set<int> spt_StationsGroup;

	std::vector<std::vector<double>> graph(StationsGroup.size(), std::vector<double>(StationsGroup.size(), 0.0));

	int idx = 0;

	for (auto& [Pp_id, edge] : Connections) {
		if (spt_StationsGroup.find(edge.EnterID) == spt_StationsGroup.end()) {
			id_idx[edge.EnterID] = idx;
			idx_id[idx] = edge.EnterID;
			spt_StationsGroup.insert(edge.EnterID);

			idx++;
		}

		if (spt_StationsGroup.find(edge.ExitID) == spt_StationsGroup.end()) {
			id_idx[edge.ExitID] = idx;
			idx_id[idx] = edge.ExitID;
			spt_StationsGroup.insert(edge.ExitID);

			idx++;
		}
	}

	for (auto& [Pp_id, edge] : Connections) {
		if (Pipeline[Pp_id].GetStatus() == 1)
			graph[id_idx[edge.EnterID]][id_idx[edge.ExitID]] = Pipeline[Pp_id].GetDiameter();
	}

	int start, finish;

	while (true) {
		std::cout << "Input start node: ";
		start = GetRightValue(std::cin, 1, INT_MAX);
		if (id_idx.find(start) != id_idx.end()) {
			start = id_idx[start];
			break;
		}
		std::cout << "There is no this node in graph" << std::endl;
	}

	while (true) {
		std::cout << "Input end node: ";
		finish = GetRightValue(std::cin, 1, INT_MAX);
		if (id_idx.find(finish) != id_idx.end()) {
			finish = id_idx[finish];
			break;
		}
		std::cout << "There is no this node in graph" << std::endl;
	}

	std::cout << "Max flow form " << idx_id[start] << " to " << idx_id[finish] << " is "
		<< FordFulkerson(graph, start, finish) << std::endl;

}