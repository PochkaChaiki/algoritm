#ifndef PIPE_H
#define PIPE_H

#include <map>
#include <fstream>

struct Pipe{
    int ID;
    int status;
    double length;
    double diameter;

    Pipe();

    void InputPipe();

    void ShowPipe();
    
    void EditPipe();
    
    void SavePipe(std::ofstream& fout);
    
    void LoadPipe(std::ifstream& fin, bool inputStatus);
};



int addPipe(std::map <int, Pipe>& pipeline, Pipe& pipe);

#endif