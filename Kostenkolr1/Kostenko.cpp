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

// template <typename T>
// void searchObjects(std::unordered_map<int, T>& objects, std::unordered_set<int>& searchResultSet){
//     // param - is actually utilitary thing. It is used to assign data type to search pipes.
//     int searchChoice;
//     std::cout<<"Choose search type by (type \"0\" to search by names or \"1\" to search by " << (std::is_same_v<T, Pipe> ? "status): " : "unused shops percentage): ");
//     searchChoice = GetRightValue(std::cin, 0, 1);
//     if (searchChoice == 0) {
//         std::string nameToSearch;
//         std::cout<<"Input keywords to search by: ";
//         std::cin.clear();
//         std::cin.ignore(INT_MAX, '\n');
//         std::getline(std::cin, nameToSearch);
//         searchResultSet = findObjectByParam(objects, checkName, nameToSearch);
//     } else if (searchChoice == 1) {
//         // auto p = (double)0;
//         std::cout << (std::is_same_v<T, Pipe> ? " Input status to search by (\"0\" for repairing pipes, \"1\" for working pipes): " : "Input unused shops percentage to search by (in fractions of a unit): ");
//         //Checks what is the object's type and according to this information passes right parameteres
//         decltype(std::is_same_v<T, Pipe> ? (int)0: (double)0) param = GetRightValue<decltype(param)>(std::cin, 0, 1);
//         searchResultSet = findObjectByParam(objects, checkParam, param);
//     }
// }

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

template <typename T>
void getObjectsToEdit(std::unordered_map<int, T>& objects, std::unordered_set<int>& searchResultSet){
    std::cout<<"Type \"0\" if you want to edit single object or \"1\" if you want to edit multiplicity of objects: "<<std::endl;
        int objectsAmount;
        objectsAmount = GetRightValue(std::cin, 0, 1);
    // Editing single object ------------------------------------------------------------------------------------------------------------------------------------    
        if (objectsAmount == 0){
            std::cout<<"Enter ID of the object you want to edit: "<<std::endl;
            int ID = GetRightValue(std::cin, 0, T::ID_counter - 1);

            while (objects.find(ID) == objects.end()){
                std::cout<<"EDIT ERROR: There's no object with this ID in your objects group. Try again."<<std::endl;
                ID = GetRightValue(std::cin, 0, T::ID_counter - 1);
            }
            searchResultSet.insert(ID);
            
    // Editing multiple objects ---------------------------------------------------------------------------------------------------------------------------------
        } else if (objectsAmount == 1){
            searchObjects(objects, searchResultSet);
            if (searchResultSet.size() != 0){
                std::cout << "Found objects: " << std::endl;
                for (auto id: searchResultSet)
                    std::cout << objects[id] << std::endl;

                std::cout << "Type \"0\" - to work with found objects, \"1\" - to choose objects to work with: ";
                int choiceOption = GetRightValue(std::cin, 0, 1);

                if (choiceOption == 1)
                    chooseIdentifiers(searchResultSet);
            } else {
                std::cout << "No objects were found." << std::endl;
            }
        }
}


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

        option = GetRightValue(std::cin, 0, 8);
        
// Checking option ------------------------------------------------------------------------------------------------------------------------
        if (option == 1){
    // Adding pipe ------------------------------------------------------------------
            Pipe pipe;
            
            std::cin >> pipe;
            myPipeline.insert({pipe.GetID(), pipe});
            std::cout << "Id currently used pipe: " << pipe.GetID() << "\n\n";

        } else if (option == 2){
    // Adding compressor station ------------------------------------------------------
            CompressorStation CS;

            std::cin >> CS;
            myStations.insert({CS.GetID(), CS});
            std::cout << "Id currently used compressor station: " << CS.GetID() << "\n\n";

        } else if (option == 3){
    // Showing all existing objects -----------------------------------------------------
            showObjects(myPipeline, myStations);

        } else if (option == 4){
    // Editing pipes -----------------------------------------------------------------------------------------------------------------------
            if (myPipeline.size() == 0){
                std::cout<<"EDIT ERROR: There're no pipes in your pipeline. Add one and try again."<<std::endl;
                continue;
            }
            std::unordered_set<int> searchResultSet;
            getObjectsToEdit(myPipeline, searchResultSet);
            int actionChoice;
                std::cout<<"Select an action for the pipe (-s) (\"0\" - to edit the pipe (-s), \"1\" - to delete the pipe (-s)): "<<std::endl;
                actionChoice = GetRightValue(std::cin, 0, 1);
                if (actionChoice == 0){
                    std::cout << "Enter status to set to pipes: ";
                    int statusToSet = GetRightValue(std::cin, 0, 1);
                    for (auto id: searchResultSet)
                        myPipeline[id].SetStatus(statusToSet);
                }
                else if (actionChoice == 1)
                    for (auto id: searchResultSet)
                        myPipeline.erase(myPipeline.find(id));
        } else if (option == 5){
    // Editing compressor stations ------------------------------------------------------------------------------------------------------------------
            if (myStations.size() == 0){
                std::cout<<"EDIT ERROR: There're no compressor stations in your stations list. Add one and try again."<<std::endl;
                continue;
            } 
            
            std::unordered_set<int> searchResultSet;
            getObjectsToEdit(myStations, searchResultSet);

            int actionChoice;
                std::cout << "Select an action for the station (-s) (\"0\" - to edit the station (-s), \"1\" - to delete the station (-s)): " << std::endl;
                actionChoice = GetRightValue(std::cin, 0, 1);
                if (actionChoice == 0){
                    for (auto id: searchResultSet)
                        myStations[id].EditCompressorStation();
                }
                else if (actionChoice == 1)
                    for (auto id: searchResultSet)
                        myStations.erase(myStations.find(id));

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
            std::unordered_set<int> searchResult;
            int choiceObject;

            std::cout<<"Choose object to use filter search on (type \"0\" for pipes or \"1\" for compressor stations): ";
            choiceObject = GetRightValue(std::cin, 0, 1);
            if (choiceObject == 0){
                searchObjects(myPipeline, searchResult);
                for (auto obj: searchResult)
                    std::cout<<myPipeline[obj]<<std::endl;
            } else if (choiceObject == 1){
                searchObjects(myStations, searchResult);
                for (auto obj: searchResult)
                    std::cout<<myStations[obj]<<std::endl;
            }
            
        }
    }
    return 0;
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
        Pipe::ID_counter = 0;
        CompressorStation::ID_counter = 0;
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
                        company.insert({CS.GetID(), CS});
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

