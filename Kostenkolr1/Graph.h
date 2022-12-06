#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <list>

#include "utils.h"


class Graph{
public:
    struct Edge{
        int EnterID;
        int ExitID;
        int EdgeID;
        friend std::ifstream& operator>> (std::ifstream& fin, Edge& e);
        friend std::ofstream& operator<< (std::ofstream& fout, Edge& e);
    };
    
    
    std::unordered_map<int, std::list<Edge>> AdjecencyList;
    
    void TopologicalSortingRecursive(int Vertice, std::unordered_map<int, int>& visited, std::stack<int>& SortedVertices);
    void Sort();
    bool CheckIsVerticeFree(int vertice);
    void Disconnect(int EdgeID);
    void FillAdjecencyList(std::unordered_map<int, Graph::Edge>& connections);
};


#endif