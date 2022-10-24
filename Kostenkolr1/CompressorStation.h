#ifndef CS_H
#define CS_H

#include <vector>
#include <unordered_map>
#include <fstream>
#include <string>

class CompressorStation{
public:
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
    
    void LoadCompressorStation(std::ifstream& fin, bool& inputStatus);
};

int addCompressorStation(std::unordered_map<int, CompressorStation>& company, CompressorStation& CS);



#endif