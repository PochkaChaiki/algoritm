#include <iostream>
#include <fstream>
#include <unordered_map>
#include <float.h>
#include <bits/stdc++.h>
#include "utils.h"
#include "Pipe.h"

int Pipe::ID_counter = 0;

Pipe::Pipe(){
    ID = ID_counter++;
    length = 0;
    diameter = 0;
    status = 0;
}

int Pipe::GetID(){return ID;}

int Pipe::GetStatus(){return status;}

void Pipe::SetStatus(int status){this->status = status;}

double Pipe::GetDiameter(){return diameter;}

//  User input pipe -------------------------------------------------------------------------------
std::istream& operator>> (std::istream& in, Pipe& pipe){
    in.ignore(INT_MAX, '\n');
    std::cout << "Input pipe's name: " << std::endl;
    std::getline(std::cin, pipe.name);
    std::cout << "Input pipe's length: ";
    pipe.length = GetRightValue(std::cin, 0.0, DBL_MAX);
    std::cout << "Input pipe's diameter: ";   
    pipe.diameter = GetRightValue(std::cin, 0.0, DBL_MAX);
    std::cout << "Input pipe's status (\"1\" if pipe is \"In work\" and \"0\" pipe is \"Repairing\"): ";
    pipe.status = GetRightValue(in, 0, 1);

    return in;
}

//  Output pipe to user's screen ------------------------------------------------------------------
std::ostream& operator<< (std::ostream& out, const Pipe& pipe)
{
    out << "Pipe parameteres: " << std::endl;
    out << "\tPipe ID: " << pipe.ID << std::endl;
    out << "\tPipe name: " << pipe.name << std::endl;
    out << "\tPipe's status: " << (pipe.status ? "In work" : "Repairing") << std::endl;
    out << "\tPipe's length: " << pipe.length << std::endl;
    out << "\tPipe's diameter: " << pipe.diameter << std::endl;
    out << "=...=...=...=...=...=...=...=...=...=...=...=...=...=...=" << std::endl;
    return out;
}

void Pipe::EditPipe(){
    std::cout << "Status value: " << status << std::endl << "Enter new value (\"0\" if pipe is \"Repairing\" and \"1\" if pipe is \"Is in work\"): ";
    status = GetRightValue(std::cin, 0, 1);
}

//  Saving pipe to a file -------------------------------------------------------------------------
std::ofstream& operator<< (std::ofstream& fout, const Pipe& pipe){
    fout << pipe.ID << "," << pipe.name << "," << pipe.status << "," << pipe.length << "," << pipe.diameter << ",";
    return fout;
}

//  Loading pipe from a file ----------------------------------------------------------------------
std::ifstream& operator>> (std::ifstream& fin, Pipe& pipe){
 
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

bool checkParam(Pipe& pipe, int param) {
    return (pipe.GetStatus() == param);
}

bool checkParam(Pipe& pipe, double param) {
    return (pipe.GetDiameter() == param);
}

void searchObjects(std::unordered_map<int, Pipe>& objects, std::unordered_set<int>& searchResultSet){
    int searchChoice;
    std::cout<<"Choose search type by (type \"0\" to search by names or \"1\" to search by status): ";
    searchChoice = GetRightValue(std::cin, 0, 1);
    if (searchChoice == 0) {
        std::string nameToSearch;
        std::cout<<"Input keywords to search by: ";
        std::cin.ignore(INT_MAX, '\n');
        std::getline(std::cin, nameToSearch);
        searchResultSet = findObjectByParam(objects, checkName, nameToSearch);
 
    } else if (searchChoice == 1) {
        std::cout << " Input status to search by (\"0\" for repairing pipes, \"1\" for working pipes): ";
        int param = GetRightValue(std::cin, 0, 1);
        searchResultSet = findObjectByParam(objects, checkParam, param);
    }
}