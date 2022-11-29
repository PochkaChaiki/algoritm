#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <list>


class Graph{
public:
    struct Edge{
        int EnterID;
        int ExitID;
        int edgeID;
    };
    
    std::unordered_map<int, std::list<Edge>> AdjecencyList;
    
    
    void TopologicalSortingRecursive(int Vertice, std::unordered_map<int, bool>& visited, std::stack<int>& SortedVertices);
    void Sort();
};


#endif