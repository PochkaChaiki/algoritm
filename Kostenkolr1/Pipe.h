#ifndef PIPE_H
#define PIPE_H

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>

class Pipe{
public:
    static int Pipe_ID_counter;

    std::string name;

    Pipe();
    ~Pipe() = default;

//  User input pipe
    friend std::istream& operator>> (std::istream& in, Pipe& pipe);

//  Output pipe to user's screen
    friend std::ostream& operator<< (std::ostream& out, const Pipe& pipe);
    
    void EditPipe();

//  Saving pipe to a file
    friend std::ofstream& operator<< (std::ofstream& fout, const Pipe& pipe);
    
//  Loading pipe from a file
    friend std::ifstream& operator>> (std::ifstream& fin, Pipe& pipe);

    int GetID();

    int GetStatus();

    void SetStatus(int status);
    
private:
    int ID;
    int status;
    double length;
    double diameter; 
};

#endif