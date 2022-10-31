#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <bits/stdc++.h>
#include "Pipe.h"
#include "CompressorStation.h"
#include "utils.h"

void showObjects(std::unordered_map <int, Pipe>& pipeline, std::unordered_map <int, CompressorStation>& company);

void loadCompany(std::unordered_map <int, Pipe>& pipeline, std::unordered_map <int, CompressorStation>& company, std::string filename);

void saveCompany(std::unordered_map <int, Pipe>& pipeline, std::unordered_map <int, CompressorStation>& company, std::string filename);

bool checkStatus(Pipe& pipe, int status) {return (pipe.GetStatus() == status);}

bool checkUnusedShops(CompressorStation& CS, double param) {return (CS.GetFreeShops() >= param);}

void searchPipes(std::unordered_map<int, Pipe>& pipeline, std::vector<int>& searchResultVector);

void searchCompressorStations(std::unordered_map<int, CompressorStation>& stations, std::vector<int>& searchResultVector);

int main(){
    int option(-1), pipeID, CSID;

    std::unordered_map <int, Pipe> myPipeline;
    std::unordered_map <int, CompressorStation> myStations;
    std::cout<<"#---------------------------------------------#"<<std::endl;
    std::cout<<"Create your own gas producing company"<<std::endl;

    while (option){
        std::cout << "#----------------------------------------------#" << std::endl;
        std::cout << "Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;"
                  << "\n5.Edit a compressor station;\n6.Save gas company;\n7.Load gas company;\n8.Find specific objects;\n0.Close program" << std::endl;

        if (!valueInput(std::cin, option)){
            std::cout<<"INPUT ERROR: Invalid input. Try again."<<std::endl;
            continue;
        }
        if (option > 8){
            std::cout<<"INPUT ERROR: Value is out of range. Try again."<<std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            option = -1;
            continue;
        }
        
// Checking option ------------------------------------------------------------------------------------------------------------------------
        if (option == 1){
    // Adding pipe ------------------------------------------------------------------
            Pipe pipe;
            
            std::cin >> pipe;
            myPipeline.insert({pipe.GetID(), pipe});
            std::cout<<"Id currently used pipe: "<<pipe.GetID()<<"\n\n";

        } else if (option == 2){
    // Adding compressor station ------------------------------------------------------
            CompressorStation CS;

            std::cin >> CS;
            myStations.insert({CS.GetID(), CS});
            std::cout<<"Id currently used compressor station: "<<CS.GetID()<<"\n\n";

        } else if (option == 3){
    // Showing all existing objects -----------------------------------------------------
            showObjects(myPipeline, myStations);

        } else if (option == 4){
    // Editing pipes -----------------------------------------------------------------------------------------------------------------------
            if (myPipeline.size() == 0){
                std::cout<<"EDIT ERROR: There're no pipes in your pipeline. Add one and try again."<<std::endl;
                continue;
            }
            
            std::cout<<"Type \"0\" if you want to edit single pipe or \"1\" if you want to edit multiplicity of pipes: "<<std::endl;
            int objectsAmount;
            while (!valueInput(std::cin, objectsAmount) || (objectsAmount < 0) || (objectsAmount > 1))
                std::cout<<"EDIT ERROR: input is invalid. Try again."<<std::endl;
        // Editing single pipe ------------------------------------------------------------------------------------------------------------------------------------    
            if (objectsAmount == 0){
                std::cout<<"Enter ID of the pipe you want to edit: "<<std::endl;
                while(!valueInput(std::cin, pipeID))
                    std::cout<<"EDIT ERROR: ID input is invalid. Try again."<<std::endl;

                if (myPipeline.find(pipeID) == myPipeline.end()){
                    std::cout<<"EDIT ERROR: There's no pipe with this ID in your pipeline. Try again."<<std::endl;
                    continue;
                }
                int actionChoice;
                std::cout<<"Select an action for the pipe (\"0\" - to edit the pipe, \"1\" - to delete the pipe): "<<std::endl;
                while (!valueInput(std::cin, actionChoice) || (actionChoice < 0) || (actionChoice > 1)){
                    std::cout<<"EDIT ERROR: Invalid action selection input"<<std::endl;
                }
                if (actionChoice == 0)
                    myPipeline[pipeID].EditPipe();
                else if (actionChoice == 1)
                    myPipeline.erase(myPipeline.find(pipeID));
        // Editing multiple pipes --------------------------------------------------------------------------------------------------------------------------------
            } else if (objectsAmount == 1){
                int findOption;
                std::cout<<"Select way to choose multiplicity of pipes (\"0\" - to find pipes with filter, \"1\" - to input pipes' identifiers by yourself): ";
                while (!valueInput(std::cin, findOption) || (findOption < 0) || (findOption > 1)){
                    std::cout<<"EDIT ERROR: Invalid input"<<std::endl;
                }
                
                if (findOption == 0){
                    std::vector<int> searchResultVector;
                    searchPipes(myPipeline, searchResultVector);
                    int statusToSet;
                    std::cout<<"Enter status to set to the pipes (\"0\" - to set \"repairing\" status, \"1\" - to set \"working\" status): ";
                    while(!valueInput(std::cin, statusToSet)|| (statusToSet < 0) || (statusToSet > 1))
                        std::cout<<"EDIT ERROR: Invalid status input"<<std::endl;
                    for (auto& id: searchResultVector)
                        myPipeline[id].SetStatus(statusToSet);
                    
                } else if (findOption == 1){
                    std::unordered_set<int> userIdentifiers;
                    int pipesAmount;
                    std::cout<<"Enter amount of pipes you want to edit: ";
                    while(!valueInput(std::cin, pipesAmount) || (pipesAmount > Pipe::Pipe_ID_counter)){
                        std::cout << "EDIT ERROR: Input error. Try again." << std::endl;
                    }
                    std::cout<<"Enter pipes' identifiers: ";
                    for (int i(0); i < pipesAmount; ++i){
                        while (!valueInput(std::cin, pipeID) || (pipeID < 0) || (pipeID > Pipe::Pipe_ID_counter) || (myPipeline.find(pipeID) == myPipeline.end()))
                            std::cout << "EDIT ERROR: Input error. Try again." << std::endl;
                        userIdentifiers.insert(pipeID);
                    }
                    std::cout << "Pipe's were found."<< std::endl;
                    int statusToSet;
                    std::cout<<"Enter status to set to the pipes (\"0\" - to set \"repairing\" status, \"1\" - to set \"working\" status): ";
                    while (!valueInput(std::cin, statusToSet)|| (statusToSet < 0) || (statusToSet > 1))
                        std::cout<<"EDIT ERROR: Invalid status input"<<std::endl;
                    for (auto& id : userIdentifiers)
                        myPipeline[id].SetStatus(statusToSet);
                }
            }
        } else if (option == 5){
    // Editing compressor stations ------------------------------------------------------------------------------------------------------------------
            if (myStations.size() == 0){
                std::cout<<"EDIT ERROR: There're no compressor stations in your stations list. Add one and try again."<<std::endl;
                continue;
            } 
            
            std::cout<<"Type \"0\" if you want to edit single compressor station or \"1\" if you want to edit multiplicity of stations: "<<std::endl;
            int objectsAmount;
            while (!valueInput(std::cin, objectsAmount) || (objectsAmount < 0) || (objectsAmount > 1))
                std::cout<<"EDIT ERROR: input is invalid. Try again."<<std::endl;
        // Editing single compressor station --------------------------------------------------------------------------------------------------------------------   
            if (objectsAmount == 0){
                std::cout<<"Enter ID of the compressor station you want to edit: "<<std::endl;
                while(!valueInput(std::cin, CSID))
                    std::cout<<"EDIT ERROR: ID input is invalid. Try again."<<std::endl;

                if ((myStations.find(CSID) == myStations.end())){
                    std::cout<<"EDIT ERROR: There's no compressor station with this ID in your stations list. Try again."<<std::endl;
                    continue;
                } 
                
                int actionChoice;
                std::cout<<"Select an action for the station (\"0\" - to edit the station, \"1\" - to delete the station): "<<std::endl;
                while (!valueInput(std::cin, actionChoice) || (actionChoice < 0) || (actionChoice > 1)){
                    std::cout<<"EDIT ERROR: Invalid action selection input"<<std::endl;
                }

                if (actionChoice == 0){
                    myStations[CSID].EditCompressorStation();
                } else if (actionChoice == 1) {
                    myStations.erase(myStations.find(CSID));
                }
        // Editing multiple compressor stations --------------------------------------------------------------------------------------------------------------------           
            } else if (objectsAmount == 1) {
                int findOption;
                std::cout<<"Select way to choose multiplicity of stations (\"0\" - to find stations with filter, \"1\" - to input stations' identifiers by yourself): ";
                while (!valueInput(std::cin, findOption) || (findOption < 0) || (findOption > 1)){
                    std::cout<<"EDIT ERROR: Invalid input"<<std::endl;
                }
                if (findOption == 0){
                    std::vector<int> searchResultVector;
                    searchCompressorStations(myStations, searchResultVector);
                    for (auto& id: searchResultVector){
                        myStations[id].EditCompressorStation();
                    }
                } else if (findOption == 1){
                    std::unordered_set<int> userIdentifiers;
                    int stationsAmount;
                    std::cout<<"Enter amount of stations you want to edit: ";
                    while(!valueInput(std::cin, stationsAmount) || (stationsAmount > CompressorStation::CS_ID_counter)){
                        std::cout << "EDIT ERROR: Input error. Try again." << std::endl;
                    }
                    std::cout<<"Enter stations' identifiers: ";
                    for (int i(0); i < stationsAmount; ++i){
                        while (!valueInput(std::cin, CSID) || (CSID < 0) || (CSID > CompressorStation::CS_ID_counter) || (myStations.find(CSID) == myStations.end()))
                            std::cout << "EDIT ERROR: ID input error. Try again." << std::endl;
                        userIdentifiers.insert(CSID);
                    }
                    std::cout << "Compressor stations were found."<< std::endl;
                    for (auto& id : userIdentifiers){
                        std::cout<<"Compressor station's id: "<<id<<std::endl;
                        myStations[id].EditCompressorStation();
                    }
                }

            }
        } else if (option == 6){
    // Saving company to file ---------------------------------------------------------------------------------------------------------------------------
            std::string filename;
            std::cout<<"Enter filename (use .save): ";
            std::cin>>filename;
            saveCompany(myPipeline, myStations, filename);
        } else if (option == 7){
    // Loading company from file ------------------------------------------------------------------------------------------------------------------------
            std::string filename;
            std::cout<<"Enter filename (use .save): ";
            std::cin>> filename;
            loadCompany(myPipeline, myStations, filename);
        } else if (option == 8){
    // Finding by filters -------------------------------------------------------------------------------------------------------------------------------
            std::vector<int> searchResult;
            int choiceObject;
            std::cout<<"Choose object to use filter search on (type \"0\" for pipes or \"1\" for compressor stations): ";
            if (!valueInput(std::cin, choiceObject) || (choiceObject < 0) || (choiceObject > 1))
                std::cout<<"INPUT ERROR: Invalid input. Try again."<<std::endl;
            else if (choiceObject == 0){
                searchPipes(myPipeline, searchResult);
                for (auto obj: searchResult)
                    std::cout<<myPipeline[obj]<<std::endl;
            } else if (choiceObject == 1){
                searchCompressorStations(myStations, searchResult);
                for (auto obj: searchResult)
                    std::cout<<myStations[obj]<<std::endl;
            }
            
        }
    }
    return 0;
}

void searchPipes(std::unordered_map<int, Pipe>& pipeline, std::vector<int>& searchResultVector){
    int searchChoice;
    std::cout<<"Choose parameter to search by (type \"0\" to search by names or \"1\" to search by status): ";
    while (!valueInput(std::cin, searchChoice) || (searchChoice < 0) || (searchChoice > 1)){
        std::cout<<"INPUT ERROR: Invalid input. Try again."<<std::endl;
    }
    if (searchChoice == 0) {
        std::string nameToSearch;
        std::cout<<"Input keywords to search by: ";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::getline(std::cin, nameToSearch);
        searchResultVector = findObjectByParam(pipeline, checkName, nameToSearch);
    } else if (searchChoice == 1) {
        int status;
        std::cout<<"Input status to search by (\"0\" for repairing pipes, \"1\" for working pipes): ";
        while (!valueInput(std::cin, status) || (status < 0) || (status > 1))
            std::cout<<"INPUT ERROR: Invalid input. Try again."<<std::endl;

        searchResultVector = findObjectByParam(pipeline, checkStatus, status);
    }
}

void searchCompressorStations(std::unordered_map<int, CompressorStation>& stations, std::vector<int>& searchResultVector){
    int searchChoice;
    std::cout<<"Choose parameter to search by (type \"0\" to search by names or \"1\" to search by unused shops percentage: ";
    if (!valueInput(std::cin, searchChoice) ||(searchChoice < 0) || (searchChoice > 1)){
        std::cout<<"INPUT ERROR: Invalid input. Try again."<<std::endl;
    }
    if (searchChoice == 0) {
        std::string nameToSearch;
        std::cout<<"Input keywords to search by: ";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::getline(std::cin, nameToSearch);
        searchResultVector = findObjectByParam(stations, checkName, nameToSearch);
    } else if (searchChoice == 1) {
        double unusedPowerSupplies;
        std::cout<<"Input unused shops percentage to search by (in fractions of a unit): ";
        while (!valueInput(std::cin, unusedPowerSupplies) || (unusedPowerSupplies < 0) || (unusedPowerSupplies > 1))
            std::cout<<"INPUT ERROR: Invalid input. Try again."<<std::endl;
        searchResultVector = findObjectByParam(stations, checkUnusedShops, unusedPowerSupplies);
    }
}

void showObjects(std::unordered_map <int, Pipe>& pipeline, std::unordered_map <int, CompressorStation>& company){
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto pipe : pipeline){
        std::cout << pipe.second;
    }
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto station: company){
        std::cout << station.second;
    }
}

void saveCompany(std::unordered_map <int, Pipe>& pipeline, std::unordered_map <int, CompressorStation>& company, std::string filename){
    std::ofstream fout(filename, std::ios::out);
    if (fout){
        fout << "Pipes: " << pipeline.size() << ",";
        for (auto pipe: pipeline)
            fout << pipe.second;

        fout << "Stations: " << company.size() << ",";
        for (auto station: company)
            fout << station.second;

        fout.close();
    } else {
        std::cout<<"WRITE ERROR: Failed to open file."<<std::endl;
    }
}

void loadCompany(std::unordered_map <int, Pipe>& pipeline, std::unordered_map <int, CompressorStation>& company, std::string filename){
    std::ifstream fin(filename, std::ios::in);
    if (fin){
        Pipe::Pipe_ID_counter = 0;
        CompressorStation::CS_ID_counter = 0;
        pipeline.clear();
        company.clear();
        std::string input;
        int amount;
        while(!fin.eof()){
            std::getline(fin, input, ' ');
            valueInput(fin, amount, ',');
            if (input == "Pipes:"){
                for (int i(0); i<amount; ++i){
                    Pipe pipe;
                    fin >> pipe;
                    if (fin.fail()){
                        std::cout<<"FILE READ ERROR: Failed to read pipe's parameters due to file's damage."<<std::endl;
                        continue;
                    } else
                        pipeline.insert({pipe.GetID(), pipe});
                    Pipe::Pipe_ID_counter = ((Pipe::Pipe_ID_counter < pipe.GetID())? pipe.GetID() : Pipe::Pipe_ID_counter);
                }
            } else if (input == "Stations:"){
                for (int j(0); j<amount; ++j){
                    CompressorStation CS;
                    fin >> CS;
                    if (fin.fail()){
                        std::cout<<"FILE READ ERROR: Failed to read compressor station's parameters due to file's damage."<<std::endl;
                        continue;
                    } else
                        company.insert({CS.GetID(), CS});
                    CompressorStation::CS_ID_counter = ((CompressorStation::CS_ID_counter < CS.GetID())? CS.GetID() : CompressorStation::CS_ID_counter);
                }
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

