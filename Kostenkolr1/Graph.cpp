#include "Graph.h"
#include <iostream>
#include <fstream>
#include <queue>

std::ifstream& operator>> (std::ifstream& fin, Graph::Edge& e){
    if (!valueInput(fin, e.EnterID, ',') || !valueInput(fin, e.ExitID, ','))
        fin.setstate(std::ios::failbit);
    
    return fin;
}

void Graph::TopologicalSortingRecursive(int vertice, std::unordered_map<int, int>& visited, std::stack<int>& SortedVertices){
    visited[vertice] = 1;

    std::list<Edge>::iterator it;
    for (it = AdjecencyList[vertice].begin(); it != AdjecencyList[vertice].end(); it++){
        try {
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
    for (auto& edge: connections)
        AdjecencyList[edge.second.EnterID].push_back(edge.second);

}

bool bfs(const std::vector<std::vector<double>> &r_graph, int s, int t, std::vector<int> &parent) {
	const int V = r_graph.size();
	std::vector<int> visited(V, 0);
	std::queue<int> q;
	int u;
	q.push(s);
	parent[s] = -1;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (int v = 0; v < V; v++) {
			if (visited[v] == false && r_graph[u][v] > 0) {
				parent[v] = u;
				if (v == t)
					return true;
				q.push(v);
				visited[v] = true;
			}
		}
	}

	return false;
}

double FordFulkerson(std::vector<std::vector<double>> &graph, int s, int t) {
	
	int u, v;
	int V = graph.size();
	std::vector<std::vector<double>> r_graph = graph;
	std::vector<int> parent(V, 0);
	double max_flow = 0;
	double path_flow;


	while (bfs(r_graph, s, t, parent)) {

		path_flow = __DBL_MAX__;

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];
			path_flow = std::min(path_flow, r_graph[u][v]);
		}

		for (v = t; v != s; v = parent[v]) {
			u = parent[v];

			r_graph[u][v] -= path_flow;
			r_graph[v][u] += path_flow;
		}

		max_flow += path_flow;
	}

	return max_flow;
}

int min_dist_node(std::unordered_set<int>& spt_set, std::vector<double>& dist) {

	double least = __DBL_MAX__;
	int idx = 0;

	for (int i(0); i < dist.size(); ++i) {
		if ((dist[i] < least) && (spt_set.find(i) == spt_set.end())) {
			least = dist[i];
			idx = i;
		}	
	}

	return idx;
}

std::vector<double> Dijkstra(std::vector<std::vector<double>> graph, int src) {

	std::unordered_set<int> spt_set;
	double Inf = __DBL_MAX__;
	std::vector<double> dist(graph.size(), Inf);
	dist[src] = 0;
	
	for (int count(0); count < (graph.size() - 1); ++count) {
		int u = min_dist_node(spt_set, dist);
		spt_set.insert(u);

		for (int v(0); v < graph.size(); ++v) {
			if ((spt_set.find(v) == spt_set.end()) && (graph[u][v] != 0) && (dist[u] != Inf))
				dist[v] = std::min(dist[v], dist[u] + graph[u][v]);
		}
	}

	return dist;
}

