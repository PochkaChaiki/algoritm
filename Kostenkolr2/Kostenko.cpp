#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>


struct Pipe {
    unsigned int ID;
    bool status = false;
    int length = 0;
    int diameter = 0;
};

struct CompressorStation {
    unsigned int ID;
    double efficiency;
    int shopsAmount = 0;
    std::vector<int> shops;
};

int addPipe(std::vector<Pipe>& pipeline, int length, int diameter, bool status);
int addCS(std::vector<CompressorStation>& company, int shopsAmount, std::vector<int>& shops);
int checkInput(std::istream& in);
void showObjects(Pipe& pipe, CompressorStation& station);
void editPipe(Pipe& pipe);
void editCompressorStation(CompressorStation& station);
void saveCompany(Pipe& pipe, CompressorStation& station);
void loadCompany(Pipe& pipe, CompressorStation& station);




int main(){
    int option(-1), pipeId, CSId;
    std::vector<Pipe> myPipeline;
    std::vector<CompressorStation> myGasCompany;

    std::cout<<"Create your own gas producing company"<<std::endl;
    std::cout<<"#---------------------------------------------#"<<std::endl;

    while (option){
        std::cout<<"Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;\n5.Edit a compressor station;\n6.Save gas company;\n7.Load gas companys\n0.Close program"<<std::endl;
        option = checkInput(std::cin);
        if (option == -1)
            continue;
        if (option > 7){
            std::cout<<"Input error. Try again."<<std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            option = -1;
            system("pause");
            system("CLS");
            continue;
        }
        
// Checking option ------------------------------------------------------------------------------------------------------------------------

        if (option == 1){
    //Adding pipe ------------------------------------------------------------------
            std::cout<<"Input pipe\'s parameteres (length, diameter, status): ";
            int length = checkInput(std::cin), diameter = checkInput(std::cin);
            bool status = checkInput(std::cin);
            // std::cin>>length>>diameter>>status;

            pipeId = addPipe(myPipeline, length, diameter, status);

            std::cout<<"Id currently used pipe: "<<pipeId<<std::endl;
            std::cout<<std::endl;

        } else if (option == 2){
    //Adding compressor station ------------------------------------------------------
            int shopsAmount;
            std::vector<int> shops;
    
            std::cout<<"Input compressor station shops' amount: ";
            shopsAmount = checkInput(std::cin);
            std::cout<<"Input compressor station each shop's status - \"1\" if it's \"in work\", and \"0\" if it is not (REMINDER: if you pass amount of statuses that is more than you wrote step back, extra statuses won't be passed): ";
            for (int i(0); i<shopsAmount; ++i){
                int status = checkInput(std::cin);
                status = (status > 1) ? 1 : status;
                if (status > -1)
                    shops.push_back(status);
                else
                    shops.push_back(0);
            }

            CSId = addCS(myGasCompany, shopsAmount, shops);
            myGasCompany[CSId].efficiency = (double)std::count(shops.begin(), shops.end(), 1) / shopsAmount;

            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout<<"Id currently used compressor station: "<<CSId<<std::endl;
            std::cout<<std::endl;

        } else if (option == 3){
    //Showing all existing objects -----------------------------------------------------
            showObjects(myPipeline[pipeId], myGasCompany[CSId]);

        } else if (option == 4){

        }

        system("pause");
        system("CLS");
    }
    return 0;
}


int checkInput(std::istream& in){
    int checkingValue;
    std::string input;
    in >> input;
    std::stringstream inputStream(input);
    if (in.fail() || !(inputStream >> checkingValue) || !inputStream.eof()){
            std::cout<<"Input error. Try again."<<std::endl;
            in.clear();
            in.ignore(INT_MAX, '\n');
            system("pause");
            system("CLS");
            return -1;
    } else {
        return checkingValue;
    }
}

void showObjects(Pipe& pipe, CompressorStation& station){
    std::cout<<"--------------------------------------------------------"<<std::endl;
    std::cout<<"Pipe parameteres: "<<std::endl;
    std::cout<<"Pipe ID: "<<pipe.ID<<std::endl;
    std::cout<<"Pipe's status: "<<(pipe.status?"In work":"Repairing")<<std::endl;
    std::cout<<"Pipe's length: "<<pipe.length<<std::endl;
    std::cout<<"Pipe's diameter: "<<pipe.diameter<<std::endl;

    std::cout<<"--------------------------------------------------------"<<std::endl;
    std::cout<<"Compressor Station's (CS) parameteres: "<<std::endl;
    std::cout<<"CS ID: "<<station.ID<<std::endl;
    std::cout<<"CS's efficiency: "<<station.efficiency * 100<<"%"<<std::endl;
    std::cout<<"CS's shops amount: "<<station.shops.size()<<std::endl;
    std::cout<<"CS's working shops amount: "<<std::count(station.shops.begin(), station.shops.end(), 1)<<std::endl;
    std::cout<<"CS's each shop's status: "<<std::endl;
    for (auto i: station.shops)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    system("pause");
}

int addPipe(std::vector<Pipe>& pipeline, int length, int diameter, bool status){
    pipeline.push_back({(unsigned int)pipeline.size(), status, length, diameter});
    return pipeline.size()-1;
}

int addCS(std::vector<CompressorStation>& company, int shopsAmount, std::vector<int>& shops){
    company.push_back({(unsigned int)company.size(), 0, shopsAmount, shops});
    return company.size()-1;
}
// std::cout<<"Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;\n5.Edit a compressor station;\n6.Save oil company;\n7.Load oil companys\n0.Close program"<<std::endl;