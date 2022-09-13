#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>


struct Pipe {
    // int id;
    bool status = false;
    int length = 0;
    int diameter = 0;
};

struct CompressorStation {
    // int id;
    int efficiency;
    int shopsAmount = 0;
    std::vector<int> shops;
};

int checkInput(std::istream& in);
void showObjects(Pipe& pipe, CompressorStation& station);
void editPipe(Pipe& pipe);
void editCompressorStation(CompressorStation& station);
void saveCompany(Pipe& pipe, CompressorStation& station);
void loadCompany(Pipe& pipe, CompressorStation& station);




int main(){
    int option(-1);
    Pipe myPipe;
    CompressorStation myCompressorStation;
    std::cout<<"Create your own oil producing company"<<std::endl;
    std::cout<<"#---------------------------------------------#"<<std::endl;
    while (option){
        std::cout<<"Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;\n5.Edit a compressor station;\n6.Save oil company;\n7.Load oil companys\n0.Close program"<<std::endl;
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
        // std::string inp
        
         // Checking option ------------------------------------------------------------------------------------------------------------------------

        if (option == 1){
            std::cout<<"Input pipe\'s parameteres (length, diameter, status): ";
            std::cin>>myPipe.length>>myPipe.diameter>>myPipe.status;
            std::cout<<std::endl;
            
        } else if (option == 2){
            std::cout<<"Input compressor station shops' parameteres (each shop's status (\"1\" if it's \"in work\", and \"0\" if it is not)): ";
            int status;

            while (std::cin>>status || std::cin.fail()){
                status = checkInput(std::cin);
                myCompressorStation.shops.push_back(status);
            }
            std::cout<<std::endl;
        } else if (option == 3){
            showObjects(myPipe, myCompressorStation);
        }
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
    std::cout<<"Pipe parameteres: "<<std::endl;
    std::cout<<"Pipe's status: "<<(pipe.status?"In work":"Repairing")<<std::endl;
    std::cout<<"Pipe's length: "<<pipe.length<<std::endl;
    std::cout<<"Pipe's diameter: "<<pipe.diameter<<std::endl;

    std::cout<<"--------------------------------------------------------"<<std::endl;
    std::cout<<"Compressor Station's (CS) parameteres: "<<std::endl;
    std::cout<<"CS's efficiency: "<<station.efficiency<<std::endl;
    std::cout<<"CS's shops amount: "<<station.shops.size()<<std::endl;
    std::cout<<"CS's working shops amount: "<<std::count(station.shops.begin(), station.shops.end(), 1)<<std::endl;
    std::cout<<"CS's each shop's status: "<<std::endl;
    for (auto i: station.shops)
        std::cout<<i<<" ";
    std::cout<<std::endl;
    system("pause");
}

// std::cout<<"Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;\n5.Edit a compressor station;\n6.Save oil company;\n7.Load oil companys\n0.Close program"<<std::endl;