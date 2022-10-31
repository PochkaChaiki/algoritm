#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bits/stdc++.h>
#include "utils.h"
#include "Pipe.h"

int Pipe::Pipe_ID_counter = 0;

Pipe::Pipe(){
    ID = Pipe_ID_counter++;
    length = 0;
    diameter = 0;
    status = 0;
}

int Pipe::GetID(){return ID;}

int Pipe::GetStatus(){return status;}

void Pipe::SetStatus(int status){this->status = status;}

//  User input pipe -------------------------------------------------------------------------------
std::istream& operator>> (std::istream& in, Pipe& pipe){
    in.clear();
    in.ignore(INT_MAX, '\n');
    std::cout<<"Input pipe's name: "<<std::endl;
    std::getline(std::cin, pipe.name);
    std::cout<<"Input pipe's length: ";
    while (!valueInput(in, pipe.length) || (pipe.length < 0)){
        std::cout<<"INPUT PIPE LENGTH ERROR: Invalid value. Try again."<<std::endl;
    }
    std::cout<<"Input pipe's diameter: ";   
    while (!valueInput(in, pipe.diameter) || (pipe.diameter < 0)){
        std::cout<<"INPUT PIPE DIAMETER ERROR: Invalid value. Try again."<<std::endl;
    }
    std::cout<<"Input pipe's status (\"1\" if pipe is \"In work\" and \"0\" pipe is \"Repairing\"): ";
    while (!valueInput(in, pipe.status) || (pipe.status < 0) || (pipe.status > 1)){
        std::cout<<"INPUT PIPE STATUS ERROR: Invalid value. Try again."<<std::endl;
    }

    return in;
}

//  Output pipe to user's screen ------------------------------------------------------------------
std::ostream& operator<< (std::ostream& out, const Pipe& pipe){
    out<<"Pipe parameteres: "<<std::endl;
    out<<"\tPipe ID: "<<pipe.ID<<std::endl;
    out<<"\tPipe name: "<<pipe.name<<std::endl;
    out<<"\tPipe's status: "<<(pipe.status?"In work":"Repairing")<<std::endl;
    out<<"\tPipe's length: "<<pipe.length<<std::endl;
    out<<"\tPipe's diameter: "<<pipe.diameter<<std::endl;
    out<<"=...=...=...=...=...=...=...=...=...=...=...=...=...=...="<<std::endl;
    return out;
}

void Pipe::EditPipe(){
    std::cout<<"Status value: "<<status<<std::endl<<"Enter new value (\"0\" if pipe is \"Repairing\" and \"1\" if pipe is \"Is in work\"): ";
    while (!valueInput(std::cin, status) || (status < 0) || (status>1)){
        std::cout<<"INPUT PIPE STATUS ERROR: Invalid value. Try again."<<std::endl;
    }
}

//  Saving pipe to a file -------------------------------------------------------------------------
std::ofstream& operator<< (std::ofstream& fout, const Pipe& pipe){
    fout<<pipe.ID<<","<<pipe.name<<","<<pipe.status<<","<<pipe.length<<","<<pipe.diameter<<",";
    return fout;
}

//  Loading pipe from a file ----------------------------------------------------------------------
std::ifstream& operator>> (std::ifstream& fin, Pipe& pipe){
    std::cout<<"Reading info about pipes"<<std::endl;
    if (!valueInput(fin, pipe.ID, ',')){
        fin.setstate(std::ios::failbit);
        return fin;
    }

    std::getline(fin, pipe.name, ',');

    if (!valueInput(fin, pipe.status, ',') || !valueInput(fin, pipe.length, ',') || !valueInput(fin, pipe.diameter, ',')){
        fin.setstate(std::ios::failbit);
    }
    return fin;
}

