#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include "utils.h" 
#include "CompressorStation.h"
#include <vector>

int CompressorStation::ID_counter = 1;

CompressorStation::CompressorStation(){
    ID = ID_counter++;
    name = "";
    efficiency = 0;
}

int CompressorStation::GetID(){return ID;}

double CompressorStation::GetFreeShops()
{
    return (double)(shops.size() - std::count(shops.begin(), shops.end(), 1)) / shops.size();
}

int CompressorStation::GetShopsAmount(){return shops.size();}

//  User input compressor station  ----------------------------------------------------------------
std::istream& operator>> (std::istream& in, CompressorStation& CS){
    std::cout<<"Input compressor station's name: ";
    std::getline(in >> std::ws, CS.name, '\n');

    std::cout << std::endl << "Input compressor station shops' amount: ";

    int shopsAmount = GetRightValue(std::cin, 0, INT_MAX);

    std::cout<< "Input compressor station each shop's status - \"1\" if it's \"in work\", and \"0\" if it is not"
             << "(REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed): ";
    
    CS.shops.reserve(shopsAmount);
    for (int i(0); i < shopsAmount; ++i){
        int status;
        status = GetRightValue(std::cin, 0, 1);
        CS.shops.push_back(status);
    }

    std::cout<<"Input compressor station's efficiency (in fraction of unit): "<<std::endl;
    CS.efficiency = GetRightValue<double>(std::cin, 0, 1);
    return in;
}

//  Output compressor station to user's screen ----------------------------------------------------
std::ostream& operator<< (std::ostream& out, const CompressorStation& CS){
    out << "Compressor Station's (CS) parameteres: " << std::endl;
    out << "\tCS ID: " << CS.ID << std::endl;
    out << "\tCS's name: " << CS.name << std::endl;
    out << "\tCS's efficiency: " << CS.efficiency * 100 << "%" << std::endl;
    out << "\tCS's shops amount: " << CS.shops.size() << std::endl;
    out << "\tCS's working shops amount: " << std::count(CS.shops.begin(), CS.shops.end(), 1) << std::endl;
    out << "\tCS's each shop's status:  ";
    
    for (auto i: CS.shops)
        out << i << " ";

    return out;
}

void CompressorStation::EditCompressorStation(){
    std::cout << "Shops statuses: " << std::endl;
    for (auto i: shops)
        std::cout << i << " ";

    std::cout << "\nEnter new shops statuses (\"1\" if it's \"in work\", and \"0\" if it is not ):"<<std::endl;

    for (auto& status: shops)
        status = GetRightValue(std::cin, 0, 1); 
    
}

//  Saving compressor station to a file -----------------------------------------------------------
std::ofstream& operator<< (std::ofstream& fout, const CompressorStation& CS){
    fout << CS.ID << "," << CS.name << "," << CS.efficiency << "," << CS.shops.size() << ",";
    for (auto shop: CS.shops)
        fout << shop << ",";
    return fout;
}

//  Loading compressor station from a file --------------------------------------------------------
std::ifstream& operator>> (std::ifstream& fin, CompressorStation& CS){
    
    if (!valueInput(fin, CS.ID, ',')){
        fin.setstate(std::ios::failbit);
        return fin;
    }
    
    std::getline(fin, CS.name, ',');
    
    int shopsAmount;
    if (!valueInput(fin, CS.efficiency, ',') || !valueInput(fin, shopsAmount, ',')){
        fin.setstate(std::ios::failbit);
        return fin;
    }

    CS.shops.reserve(shopsAmount);
    for (int i(0); i < shopsAmount; ++i){
        int status;
        if (!valueInput(fin, status, ',') || (status < 0) || (status > 1)){
            fin.setstate(std::ios::failbit);
            CS.shops.clear();
            fin.ignore(shopsAmount - (i + 1), ',');
            return fin;
        } else
            CS.shops.push_back(status);
    }
    
    return fin;
}

bool checkParam(CompressorStation& CS, double param) {
    return (CS.GetFreeShops() >= param);
}


void searchObjects(std::unordered_map<int, CompressorStation>& objects, std::unordered_set<int>& searchResultSet){
    int searchChoice;
    std::cout<<"Choose search type by (type \"0\" to search by names or \"1\" to search by unused shops percentage): ";
    searchChoice = GetRightValue(std::cin, 0, 1);
    if (searchChoice == 0) {
        std::string nameToSearch;
        std::cout<<"Input keywords to search by: ";
        std::cin.clear();
        std::cin.ignore(INT_MAX, '\n');
        std::getline(std::cin, nameToSearch);
        searchResultSet = findObjectByParam(objects, checkName, nameToSearch);
    } else if (searchChoice == 1) {
        std::cout << "Input unused shops percentage to search by (in fractions of a unit): ";
        double param = GetRightValue<double>(std::cin, 0, 1);
        searchResultSet = findObjectByParam(objects, checkParam, param);
    }
}