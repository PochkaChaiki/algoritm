#include "Graph.h"
#include <iostream>

void Graph::TopologicalSortingRecursive(int vertice, std::unordered_map<int, bool>& visited, std::stack<int>& SortedVertices){
    visited[vertice] = true;

    std::list<Edge>::iterator it;
    for (it = AdjecencyList[vertice].begin(); it != AdjecencyList[vertice].end(); it++){
        if (!visited[it -> ExitID])
            TopologicalSortingRecursive((*it).ExitID, visited, SortedVertices);
    }

    SortedVertices.push(vertice);
}

void Graph::Sort(){
    std::stack<int> SortedVertices;
    std::unordered_map<int, bool> visited;
    for (auto& v: AdjecencyList)
        visited.insert({v.first, false});
    for (auto& v: AdjecencyList){
        if (!visited[v.first])
            TopologicalSortingRecursive(v.first, visited, SortedVertices);
    }

    while (SortedVertices.empty() == false){
        std::cout<<SortedVertices.top()<<" \n";
        SortedVertices.pop();
    }
}