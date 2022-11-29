#ifndef CS_H
#define CS_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

class CompressorStation{
public:
    static int ID_counter;
    int topid;
    std::string name;

    CompressorStation();
    ~CompressorStation() = default;

//  User input compressor station
    friend std::istream& operator>> (std::istream& in, CompressorStation& CS);

//  Output compressor station to user's screen
    friend std::ostream& operator<< (std::ostream& out, const CompressorStation& CS);

    void EditCompressorStation();

//  Saving compressor station to a file
    friend std::ofstream& operator<< (std::ofstream& fout, const CompressorStation& CS);
    
//  Loading compressor station from a file
    friend std::ifstream& operator>> (std::ifstream& fin, CompressorStation& CS);

    int GetID();
    
    double GetFreeShops(); 

private:
    int ID;
    double efficiency;
    std::vector<int> shops;
    std::unordered_set<int> connectedPipes;
};

bool checkParam(CompressorStation& CS, double param);

void searchObjects(std::unordered_map<int, CompressorStation>& objects, std::unordered_set<int>& searchResultSet);

#endif