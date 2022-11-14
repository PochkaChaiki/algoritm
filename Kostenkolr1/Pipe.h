#ifndef PIPE_H
#define PIPE_H

#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <iostream>
#include <string>

class Pipe{
public:
    static int ID_counter;

    std::string name;

    Pipe();
    ~Pipe() = default;

//  User input pipe
    friend std::istream& operator>> (std::istream& in, Pipe& pipe);

//  Output pipe to user's screen
    friend std::ostream& operator<< (std::ostream& out, const Pipe& pipe);

//  Saving pipe to a file
    friend std::ofstream& operator<< (std::ofstream& fout, const Pipe& pipe);
    
//  Loading pipe from a file
    friend std::ifstream& operator>> (std::ifstream& fin, Pipe& pipe);

    int GetID();

    int GetStatus();

    void SetStatus(int status);
    
    void EditPipe();   
private:
    int ID;
    int status;
    double length;
    double diameter; 
};

bool checkParam(Pipe& pipe, int param);

void searchObjects(std::unordered_map<int, Pipe>& objects, std::unordered_set<int>& searchResultSet);

#endif