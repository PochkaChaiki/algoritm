#include "Graph.h"
#include <iostream>
#include <fstream>

std::ifstream& operator>> (std::ifstream& fin, Graph::Edge& e){
    if (!valueInput(fin, e.EnterID, ',') || !valueInput(fin, e.ExitID, ',')){
        fin.setstate(std::ios::failbit);
    }
    return fin;
}

void Graph::TopologicalSortingRecursive(int vertice, std::unordered_map<int, int>& visited, std::stack<int>& SortedVertices){
    visited[vertice] = 1;

    std::list<Edge>::iterator it;
    for (it = AdjecencyList[vertice].begin(); it != AdjecencyList[vertice].end(); it++){
        try{
        if (visited[it -> ExitID] == 0)
            TopologicalSortingRecursive((*it).ExitID, visited, SortedVertices);
        else if (visited[it -> ExitID] == 1)
            throw std::string("Loop in graph\n");
        } catch(...){
            throw;
        }
    }
    visited[vertice] = 2;
    SortedVertices.push(vertice);
}

void Graph::Sort(){
    std::stack<int> SortedVertices;
    std::unordered_map<int, int> visited;
    // std::unordered_map<int, bool> greyVertices;
    for (auto& v: AdjecencyList)
        visited.insert({v.first, 0});
    
    for (auto& v: AdjecencyList){
        try{
        if (!visited[v.first])
            TopologicalSortingRecursive(v.first, visited, SortedVertices);
        } catch (std::string error) {
            std::cout << error;
            return;
        }
    }
    
    while (SortedVertices.empty() == false){
        std::cout << SortedVertices.top() << " ";
        SortedVertices.pop();
    }
    std::cout << "\n";

}

void Graph::FillAdjecencyList(std::unordered_map<int, Graph::Edge>& connections){
    for (auto& edge: connections){
        AdjecencyList[edge.second.EnterID].push_back(edge.second);
    };

}