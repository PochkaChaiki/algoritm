#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include "utils.h" 
#include "CompressorStation.h"
#include <vector>

int CompressorStation::CS_ID_counter = 0;

CompressorStation::CompressorStation(){
    ID = CS_ID_counter++;
    name = "";
    efficiency = 0;
}

int CompressorStation::GetID(){return ID;}

double CompressorStation::GetFreeShops(){return (double)(shops.size() - std::count(shops.begin(), shops.end(), 1))/shops.size();}

//  User input compressor station  ----------------------------------------------------------------
std::istream& operator>> (std::istream& in, CompressorStation& CS){
    std::cout<<"Input compressor station's name (REMINDER: single word): ";
    in.clear();
    in.ignore(INT_MAX, '\n');
    std::getline(in, CS.name, '\n');

    std::cout<<std::endl;

    std::cout<<"Input compressor station shops' amount: ";

    int shopsAmount;
    while (!valueInput(in, shopsAmount)){
        std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
    }

    std::cout<<"Input compressor station each shop's status - \"1\" if it's \"in work\", and \"0\" if it is not"
             << "(REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed): ";
    for (int i(0); i < shopsAmount; ++i){
        int status;
        if (!valueInput(in, status) || (status < 0) || (status > 1)){
            std::cout<<"INPUT ERROR: Invalid values. Try again."<<std::endl;
            CS.shops.clear();
            i = -1;
            in.clear();
            std::cout<<"Press Enter to continue...";
            in.ignore(INT_MAX, '\n');
        } else 
            CS.shops.push_back(status);
    }
    // Clearing input to be sure that no garbage will be read in afterwards.
    in.clear();
    in.ignore(INT_MAX, '\n');

    std::cout<<"Input compressor station's efficiency (in fraction of unit): "<<std::endl;
    while (!valueInput(in, CS.efficiency) || (CS.efficiency < 0) || (CS.efficiency > 1)){
        std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
    }


    return in;
}

//  Output compressor station to user's screen ----------------------------------------------------
std::ostream& operator<< (std::ostream& out, const CompressorStation& CS){
    out<<"Compressor Station's (CS) parameteres: "<<std::endl;
    out<<"\tCS ID: "<<CS.ID<<std::endl;
    out<<"\tCS's name: "<<CS.name<<std::endl;
    out<<"\tCS's efficiency: "<<CS.efficiency * 100<<"%"<<std::endl;
    out<<"\tCS's shops amount: "<<CS.shops.size()<<std::endl;
    out<<"\tCS's working shops amount: "<<std::count(CS.shops.begin(), CS.shops.end(), 1)<<std::endl;
    out<<"\tCS's each shop's status: "<<std::endl;
    for (auto i: CS.shops)
        out<<i<<" ";
    out<<std::endl;
    out<<"=...=...=...=...=...=...=...=...=...=...=...=...=...=...="<<std::endl;
    return out;
}

void CompressorStation::EditCompressorStation(){
    std::cout<<"Shops statuses: "<<std::endl;
    for (auto i: shops)
        std::cout<<i<<" ";

    std::cout<<"\nEnter new shops statuses (\"1\" if it's \"in work\", and \"0\" if it is not "
             <<"(REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed)): "<<std::endl;

    int shopsAmount = shops.size();
    shops.clear(); 

    for (int i(0); i < shopsAmount; ++i){
        int status;
        if (!valueInput(std::cin, status) || (status < 0) || (status > 1)){
            std::cout<<"INPUT ERROR: Invalid value. Try again."<<std::endl;
            shops.clear();
            i = -1;
            std::cin.clear();
            std::cout<<"Press Enter to continue...";
            std::cin.ignore(INT_MAX, '\n');
        } else
            shops.push_back(status);
    }
}

//  Saving compressor station to a file -----------------------------------------------------------
std::ofstream& operator<< (std::ofstream& fout, const CompressorStation& CS){
    fout<<CS.ID<<","<<CS.name<<","<<CS.efficiency<<","<<CS.shops.size()<<",";
    for (auto shop: CS.shops)
        fout<<shop<<",";
    return fout;
}

//  Loading compressor station from a file --------------------------------------------------------
std::ifstream& operator>> (std::ifstream& fin, CompressorStation& CS){
    std::cout<<"Reading info about stations"<<std::endl;
    
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
