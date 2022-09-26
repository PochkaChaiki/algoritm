#ifndef CS_H
#define CS_H

#include <vector>
#include <map>
#include <fstream>
#include <string>

struct CompressorStation{
    int ID;
    std::string stationName;
    double efficiency;
    int shopsAmount;
    std::vector<int> shops;

    CompressorStation();

    void InputCompressorStation();

    void ShowCompressorStation();

    void EditCompressorStation();

    void SaveCompressorStation(std::ofstream& fout);
    
    void LoadCompressorStation(std::ifstream& fin, bool inputStatus);
};

int addCompressorStation(std::map<int, CompressorStation>& company, CompressorStation& CS);

#endif