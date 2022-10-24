#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include "utils.h" 
#include "CompressorStation.h"
#include <vector>

CompressorStation::CompressorStation(){
    ID = -1;
    stationName = "";
    efficiency = 0;
    shopsAmount = 0;
}

void CompressorStation::InputCompressorStation(){
    std::cout<<"Input compressor station's name (REMINDER: single word): ";
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::getline(std::cin, stationName, '\n');

    std::cout<<std::endl;

    std::cout<<"Input compressor station shops' amount: ";

    while (!valueInput(std::cin, shopsAmount)){
        std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
    }

    std::cout<<"Input compressor station each shop's status - \"1\" if it's \"in work\", and \"0\" if it is not (REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed): ";
    for (int i(0); i<shopsAmount; ++i){
        int status;
        if (!valueInput(std::cin, status) || (status < 0) || (status > 1)){
            std::cout<<"INPUT ERROR: Invalid values. Try again."<<std::endl;
            shops.clear();
            i = 0;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        } else 
            shops.push_back(status);
    }

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    efficiency = (double)std::count(shops.begin(), shops.end(), 1) / shopsAmount;
}

void CompressorStation::ShowCompressorStation(){
    std::cout<<"Compressor Station's (CS) parameteres: "<<std::endl;
    std::cout<<"\tCS ID: "<<ID<<std::endl;
    std::cout<<"\tCS's name: "<<stationName<<std::endl;
    std::cout<<"\tCS's efficiency: "<<efficiency * 100<<"%"<<std::endl;
    std::cout<<"\tCS's shops amount: "<<shops.size()<<std::endl;
    std::cout<<"\tCS's working shops amount: "<<std::count(shops.begin(), shops.end(), 1)<<std::endl;
    std::cout<<"\tCS's each shop's status: "<<std::endl;
    for (auto i: shops)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    std::cout<<"=...=...=...=...=...=...=...=...=...=...=...=...=...=...="<<std::endl;
}

void CompressorStation::EditCompressorStation(){
    std::cout<<"Shops statuses: "<<std::endl;
    for (auto i: shops)
        std::cout<<i<<" ";

    std::cout<<"\nEnter new shops statuses (\"1\" if it's \"in work\", and \"0\" if it is not (REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed)): "<<std::endl;
    shops.clear(); 

    for (int i(0); i<shopsAmount; ++i){
        int status;
        if (!valueInput(std::cin, status) || (status < 0) || (status > 1)){
            std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
            shops.clear();
            i = 0;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        } else
            shops.push_back(status);
    }
    efficiency = (double)std::count(shops.begin(), shops.end(), 1) / shopsAmount;
}

void CompressorStation::SaveCompressorStation(std::ofstream& fout){
    // fout<<ID<<" \""<<stationName<<"\" "<<efficiency<<" "<<shopsAmount;
    // for (auto shop: shops)
    //     fout<<" "<<shop;
    // fout<<std::endl;

    fout<<ID<<","<<stationName<<","<<efficiency<<","<<shopsAmount<<",";
    for (auto shop: shops)
        fout<<shop<<",";
}

void CompressorStation::LoadCompressorStation(std::ifstream& fin, bool& inputStatus){
    std::cout<<"Reading info about stations"<<std::endl;
    
    if (!valueInput(fin, ID, ',')){
        inputStatus = false;
        return;
    }
    
    std::getline(fin, stationName, ',');
    

    if (!valueInput(fin, efficiency, ',') || !valueInput(fin, shopsAmount, ',')){
        inputStatus = false;
        return;
    }

    for (int i(0); i<shopsAmount; ++i){
        int status;
        if (!valueInput(fin, status, ',')|| (status < 0) || (status > 1)){
            inputStatus = false;
            shops.clear();
            std::cin.clear();
            std::cin.ignore(shopsAmount - (i + 1), ',');
            // return;
        } else
            shops.push_back(status);
    }
}

int addCompressorStation(std::unordered_map <int, CompressorStation>& company, CompressorStation& CS){
    CS.ID = company.size(); // need to find other way to ID cs ------------------------!
    company.insert({CS.ID, CS});
    return CS.ID;
}