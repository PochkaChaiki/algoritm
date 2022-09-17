#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

#define INT_TYPE (int)1
#define DOUBLE_TYPE (double)1.0
// #define UNSIGNED_INT_TYPE (unsigned int)1


struct Pipe {
    unsigned int ID;
    bool status = false;
    double length = 0;
    double diameter = 0;
};

struct CompressorStation {
    unsigned int ID;
    double efficiency;
    int shopsAmount = 0;
    std::vector<int> shops;
};

template <typename T>
T checkInput(std::istream& in, T checkingValue){
    std::string input;
    in >> input;
    std::stringstream inputStream(input);
    if (in.fail() || !(inputStream >> checkingValue) || !inputStream.eof()){
            std::cout<<"Input error. Try again."<<std::endl;
            in.clear();
            in.ignore(INT_MAX, '\n');
            system("pause");
            // system("CLS");
            return -1;
    } else {
        return checkingValue;
    }
}

void showObjects(std::vector<Pipe>& pipeline, std::vector<CompressorStation>& company){
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto pipe : pipeline){
        std::cout<<"Pipe parameteres: "<<std::endl;
        std::cout<<"\tPipe ID: "<<pipe.ID<<std::endl;
        std::cout<<"\tPipe's status: "<<(pipe.status?"In work":"Repairing")<<std::endl;
        std::cout<<"\tPipe's length: "<<pipe.length<<std::endl;
        std::cout<<"\tPipe's diameter: "<<pipe.diameter<<std::endl;
        std::cout<<"=...=...=...=...=...=...=...=...=...=...=...=...=...=...="<<std::endl;
    }

    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto station: company){
        std::cout<<"Compressor Station's (CS) parameteres: "<<std::endl;
        std::cout<<"\tCS ID: "<<station.ID<<std::endl;
        std::cout<<"\tCS's efficiency: "<<station.efficiency * 100<<"%"<<std::endl;
        std::cout<<"\tCS's shops amount: "<<station.shops.size()<<std::endl;
        std::cout<<"\tCS's working shops amount: "<<std::count(station.shops.begin(), station.shops.end(), 1)<<std::endl;
        std::cout<<"\tCS's each shop's status: "<<std::endl;
        for (auto i: station.shops)
            std::cout<<i<<" ";
        std::cout<<std::endl;
        std::cout<<"=...=...=...=...=...=...=...=...=...=...=...=...=...=...="<<std::endl;
    }
    system("pause");
}

int addPipe(std::vector<Pipe>& pipeline, double length, double diameter, bool status){
    pipeline.push_back({(unsigned int)pipeline.size(), status, length, diameter});
    return pipeline.size()-1;
}

int addCompressorStation(std::vector<CompressorStation>& company, int shopsAmount, std::vector<int>& shops){
    company.push_back({(unsigned int)company.size(), 0, shopsAmount, shops});
    return company.size()-1;
}

void editPipe(Pipe& pipe, int option){
    if (option == 1){
        std::cout<<"Status value: "<<pipe.status<<std::endl<<"Enter new value (\"0\" if pipe is \"Repairing\" and \"1\" if pipe is \"Is in work\"): ";
        int statusInput = checkInput(std::cin, INT_TYPE);
        pipe.status = (statusInput <= -1) ? pipe.status : statusInput;
        
    } else if (option == 2){
        std::cout<<"Length value: "<<pipe.length<<std::endl<<"Enter new value: ";
        double lengthInput = checkInput(std::cin, DOUBLE_TYPE);
        pipe.length = (lengthInput <= -1) ? pipe.length : lengthInput;
    } else if (option == 3){
        std::cout<<"Diameter value: "<<pipe.diameter<<std::endl<<"Enter new value: ";
        double diameterInput = checkInput(std::cin, DOUBLE_TYPE);
        pipe.diameter = (diameterInput <= -1) ? pipe.diameter : diameterInput;
    }
}   

void editCompressorStation(CompressorStation& station, int option){
    if (option == 1){
        std::cout<<"Shops amount value: "<<station.shopsAmount<<std::endl<<"Enter new value: ";
        int shopsAmountInput = checkInput(std::cin, INT_TYPE);
        station.shopsAmount = (shopsAmountInput <= -1) ? station.shopsAmount : shopsAmountInput;
        if (station.shops.size() < station.shopsAmount){
            for (int j(0); j < station.shopsAmount - station.shops.size(); ++j)
                station.shops.push_back(0);
        } else if (station.shops.size() > station.shopsAmount){
            for (int j(0); j < station.shops.size() - station.shopsAmount; ++j)
                station.shops.pop_back();
        }
        station.efficiency = (double)std::count(station.shops.begin(), station.shops.end(), 1) / station.shopsAmount;

    } else if (option == 2){
        std::cout<<"Shops statuses: "<<std::endl;
        for (auto i: station.shops)
            std::cout<<i<<" ";
        std::cout<<"Enter new shops statuses (\"1\" if it's \"in work\", and \"0\" if it is not (REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed)): "<<std::endl;
        station.shops.clear();
        for (int i(0); i<station.shopsAmount; ++i){
                int status = checkInput(std::cin, INT_TYPE);
                status = (status > 1) ? 1 : status;
                if (status > -1)
                    station.shops.push_back(status);
                else if (status == -1){
                    i--;
                    continue;
                }else
                    station.shops.push_back(0);
            }
        station.efficiency = (double)std::count(station.shops.begin(), station.shops.end(), 1) / station.shopsAmount;
    }

}

void saveCompany(std::vector <Pipe>& pipeline, std::vector <CompressorStation>& company, std::string filename){
    std::ofstream fout(filename, std::ios::out);
    fout<<"Pipes:"<<std::endl;
    for (auto pipe: pipeline)
        fout<<pipe.ID<<","<<pipe.status<<","<<pipe.length<<","<<pipe.diameter<<std::endl;
    fout<<"Stations:"<<std::endl;
    for (auto station: company){
        fout<<station.ID<<","<<station.efficiency<<","<<station.shopsAmount;
        for (auto shop: station.shops)
            fout<<","<<shop;
        fout<<std::endl;
    }
    fout.close();
}