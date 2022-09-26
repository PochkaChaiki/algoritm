#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bits/stdc++.h>
#include "Pipe.h"
#include "CompressorStation.h"
#include "company.h"

void showObjects(std::map <int, Pipe>& pipeline, std::map <int, CompressorStation>& company);

void loadCompany(std::map <int, Pipe>& pipeline, std::map <int, CompressorStation>& company, std::string filename);

void saveCompany(std::map <int, Pipe>& pipeline, std::map <int, CompressorStation>& company, std::string filename);

int main(){
    int option(-1), pipeID, CSID;

    std::map <int, Pipe> myPipeline;
    std::map <int, CompressorStation> myStations;
    std::cout<<"#---------------------------------------------#"<<std::endl;
    std::cout<<"Create your own gas producing company"<<std::endl;
    std::cout<<"#---------------------------------------------#"<<std::endl;

    while (option){
        std::cout<<"Choose menu's option:\n1.Add a pipe;\n2.Add a compressor station;\n3.Show all objects;\n4.Edit a pipe;\n5.Edit a compressor station;\n6.Save gas company;\n7.Load gas company;\n0.Close program"<<std::endl;
        option = checkInput(std::cin, INT_TYPE);
        if (option == -1)
            continue;
        if (option > 7){
            std::cout<<"INPUT ERROR: Value is out of range. Try again."<<std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            option = -1;
            continue;
        }
        
// Checking option ------------------------------------------------------------------------------------------------------------------------
        if (option == 1){
    //Adding pipe ------------------------------------------------------------------
            Pipe pipe;
            
            pipe.InputPipe();
            pipeID = addPipe(myPipeline, pipe);

            std::cout<<"Id currently used pipe: "<<pipeID<<std::endl;
            std::cout<<std::endl;

        } else if (option == 2){
    //Adding compressor station ------------------------------------------------------
            CompressorStation CS;

            CS.InputCompressorStation();
            CSID = addCompressorStation(myStations, CS);

            std::cout<<"Id currently used compressor station: "<<CSID<<std::endl;
            std::cout<<std::endl; 

        } else if (option == 3){
    //Showing all existing objects -----------------------------------------------------
            showObjects(myPipeline, myStations);

        } else if (option == 4){
    //Editing pipes -----------------------------------------------------------------------------------------------------------------------
            if (myPipeline.size() == 0){
                std::cout<<"EDIT ERROR: There're no pipes in your pipeline. Add one and try again."<<std::endl;
                continue;
            }
            std::cout<<"Enter ID of the pipe you want to edit: "<<std::endl;
            pipeID = checkInput(std::cin, INT_TYPE);
            if (pipeID > myPipeline.size() - 1){
                std::cout<<"EDIT ERROR: There's no pipe with this ID in your pipeline. Try again."<<std::endl;
                continue;
            }
            if (pipeID == -1){
                std::cout<<"EDIT ERROR: ID input is invalid. Try again."<<std::endl;
                continue;
            }
            myPipeline[pipeID].EditPipe();

        } else if (option == 5){
    //Editing compressor stations ------------------------------------------------------------------------------------------------------------------
            if (myStations.size() == 0){
                std::cout<<"EDIT ERROR: There're no compressor stations in your stations list. Add one and try again."<<std::endl;
                continue;
            }
            std::cout<<"Enter ID of the compressor station you want to edit: "<<std::endl;
            CSID = checkInput(std::cin, INT_TYPE);

            if ((CSID > myStations.size() - 1)){
                std::cout<<"EDIT ERROR: There's no compressor station with this ID in your stations list. Try again."<<std::endl;
                continue;
            }
            if (CSID == -1){
                std::cout<<"EDIT ERROR: ID input is invalid. Try again."<<std::endl;
                continue;
            }
            
            myStations[CSID].EditCompressorStation();

        } else if (option == 6){
    //Saving company to file ---------------------------------------------------------------------------------------------------------------------------
            std::string filename;
            std::cout<<"Enter filename (use .save): ";
            std::cin>>filename;
            saveCompany(myPipeline, myStations, filename);
        } else if (option == 7){
    //Loading company from file ------------------------------------------------------------------------------------------------------------------------
            std::string filename;
            std::cout<<"Enter filename (use .save): ";
            std::cin>> filename;
            loadCompany(myPipeline, myStations, filename);
        }
    }
    return 0;
}

void showObjects(std::map <int, Pipe>& pipeline, std::map <int, CompressorStation>& company){
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto pipe : pipeline){
        pipe.second.ShowPipe();
    }
    std::cout<<"#--------------------------------------------------------#"<<std::endl;
    for (auto station: company){
        station.second.ShowCompressorStation();
    }
}

void saveCompany(std::map <int, Pipe>& pipeline, std::map <int, CompressorStation>& company, std::string filename){
    std::ofstream fout(filename, std::ios::out);
    if (fout){
        fout<<"Pipes: "<<pipeline.size()<<std::endl;
        for (auto pipe: pipeline)
            pipe.second.SavePipe(fout);

        fout<<"Stations: "<<company.size();
        for (auto station: company)
            station.second.SaveCompressorStation(fout);

        fout.close();
    } else {
        std::cout<<"WRITE ERROR: Failed to open file."<<std::endl;
    }
}

void loadCompany(std::map <int, Pipe>& pipeline, std::map <int, CompressorStation>& company, std::string filename){
    std::ifstream fin(filename, std::ios::in);
    if (fin){
        pipeline.clear();
        company.clear();
        std::string input;
        int amount;
        while(!fin.eof()){
            std::getline(fin, input, ' ');
            fin >> amount;
            if (input == "Pipes:"){
                for (int i(0); i<amount; ++i){
                    Pipe pipe;
                    bool flag(false);
                    pipe.LoadPipe(fin, flag);
                    if (flag){
                        std::cout<<"FILE READ ERROR: Failed to read pipe's parameters due to file's damage."<<std::endl;
                        continue;
                    } else
                        pipeline.insert({pipe.ID, pipe});
                }
                std::getline(fin, input, '\n');
            }else if (input == "Stations:"){
                for (int j(0); j<amount; ++j){
                    CompressorStation CS;
                    bool flag(false);
                    CS.LoadCompressorStation(fin, flag);
                    if (flag){
                        std::cout<<"FILE READ ERROR: Failed to read compressor station's parameters due to file's damage."<<std::endl;
                        continue;
                    } else
                        company.insert({CS.ID, CS});
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

