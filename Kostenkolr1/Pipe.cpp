#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include "utils.h"
#include "Pipe.h"

Pipe::Pipe(){
    ID = -1;
    length = 0;
    diameter = 0;
    status = 0;
}

void Pipe::InputPipe(){
    std::cout<<"Input pipe's length: ";
    while (!valueInput(std::cin, length) || (length < 0)){
        std::cout<<"INPUT PIPE LENGTH ERROR: Invalid value. Try again."<<std::endl;
    }
    std::cout<<"Input pipe's diameter: ";   
    while (!valueInput(std::cin, diameter) || (diameter < 0)){
        std::cout<<"INPUT PIPE DIAMETER ERROR: Invalid value. Try again."<<std::endl;
    }
    std::cout<<"Input pipe's status (\"1\" if pipe is \"In work\" and \"0\" pipe is \"Repairing\"): ";
    while (!valueInput(std::cin, status) || (status < 0) || (status > 1)){
        std::cout<<"INPUT PIPE STATUS ERROR: Invalid value. Try again."<<std::endl;
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
    while (!valueInput(std::cin, status) || (status < 0) || (status>1)){
        std::cout<<"INPUT PIPE STATUS ERROR: Invalid value. Try again."<<std::endl;
    }
}

void Pipe::SavePipe(std::ofstream& fout){
    fout<<ID<<","<<status<<","<<length<<","<<diameter<<",";
}

void Pipe::LoadPipe(std::ifstream& fin, bool& inputStatus){
    std::cout<<"Reading info about pipes"<<std::endl;
    if (!valueInput(fin, ID, ',') || !valueInput(fin, status, ',') || !valueInput(fin, length, ',') || !valueInput(fin, diameter, ','))
        inputStatus = false;
}

int addPipe(std::unordered_map <int, Pipe>& pipeline, Pipe& pipe){
    pipe.ID = pipeline.size(); // need to find better way to id pipes --------------------!
    pipeline.insert({pipe.ID, pipe});
    return pipe.ID;
}