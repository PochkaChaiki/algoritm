#ifndef GASCOMPANY_H
#define GASCOMPANY_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils.h"
#include "Pipe.h"
#include "CompressorStation.h"
#include "Graph.h"

class GasCompany {
public:
    std::string name;
    std::unordered_map <int, Pipe> Pipeline;
    std::unordered_map <int, CompressorStation> StationsGroup;

    Graph Network;
    // std::vector<std::vector<int>> Matrix;

    
    void showObjects();
    void saveCompany(std::string filename); 
    void loadCompany(std::string filename);
    void addCS();
    void addConnection();
    void editPipes();
    void editCompressorStations();
    void findObjects();
    void unlink();
};

void chooseIdentifiers(std::unordered_set<int>& idSet);

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

void fillMatrix();



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

#endif