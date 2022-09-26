#include <iostream>
#include <fstream>
#include <map>
#include <bits/stdc++.h>
#include "company.h"
#include "Pipe.h"

Pipe::Pipe(){
    ID = -1;
    length = 0;
    diameter = 0;
    status = 0;
}

void Pipe::InputPipe(){
    std::cout<<"Input pipe's length: ";
    length = checkInput(std::cin, DOUBLE_TYPE);
    while (length < 0){
        std::cout<<"INPUT PIPE LENGTH ERROR: Invalid value. Try again."<<std::endl;
        length = checkInput(std::cin, DOUBLE_TYPE);
    }
    std::cout<<"Input pipe's diameter: ";   
    diameter = checkInput(std::cin, DOUBLE_TYPE);
    while (diameter < 0){
        std::cout<<"INPUT PIPE DIAMETER ERROR: Invalid value. Try again."<<std::endl;
        diameter = checkInput(std::cin, DOUBLE_TYPE);
    }
    std::cout<<"Input pipe's status (\"1\" if pipe is \"In work\" and \"0\" pipe is \"Repairing\"): ";
    status = checkInput(std::cin, INT_TYPE);
    while ((status < 0) || (status > 1)){
        std::cout<<"INPUT PIPE STATUS ERROR: Invalid value. Try again."<<std::endl;
        status = checkInput(std::cin, INT_TYPE);
    }
}

void Pipe::ShowPipe(){
    std::cout<<"Pipe parameteres: "<<std::endl;
    std::cout<<"\tPipe ID: "<<ID<<std::endl;
    std::cout<<"\tPipe's status: "<<(status?"In work":"Repairing")<<std::endl;
    std::cout<<"\tPipe's length: "<<length<<std::endl;
    std::cout<<"\tPipe's diameter: "<<diameter<<std::endl;
    std::cout<<"=...=...=...=...=...=...=...=...=...=...=...=...=...=...="<<std::endl;
}

void Pipe::EditPipe(){
    std::cout<<"Status value: "<<status<<std::endl<<"Enter new value (\"0\" if pipe is \"Repairing\" and \"1\" if pipe is \"Is in work\"): ";
    status = checkInput(std::cin, INT_TYPE);
    while ((status < 0) || (status>1)){
        std::cout<<"INPUT PIPE STATUS ERROR: Invalid value. Try again."<<std::endl;
        status = checkInput(std::cin, INT_TYPE);
    }
}

void Pipe::SavePipe(std::ofstream& fout){
    fout<<ID<<" "<<status<<" "<<length<<" "<<diameter<<std::endl;
}

void Pipe::LoadPipe(std::ifstream& fin, bool inputStatus){
    std::cout<<"Reading info about pipes"<<std::endl;
    ID = checkInput(fin, INT_TYPE);
    status = checkInput(fin, INT_TYPE);
    length = checkInput(fin, DOUBLE_TYPE);
    diameter = checkInput(fin, DOUBLE_TYPE);
    
    if ((ID == -1) || (status == -1) || (length == -1) || (diameter == -1))
        inputStatus = true;
    else 
        inputStatus = false;
}

int addPipe(std::map <int, Pipe>& pipeline, Pipe& pipe){
    pipe.ID = pipeline.size();
    pipeline.insert({pipe.ID, pipe});
    return pipe.ID;
}