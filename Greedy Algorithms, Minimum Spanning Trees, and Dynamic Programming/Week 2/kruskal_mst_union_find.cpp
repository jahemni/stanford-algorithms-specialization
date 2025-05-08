// kruskal_mst_union_find.cpp
// ------------------------------------------------------------------------
// Kruskal’s algorithm to compute the Minimum Spanning Tree (MST) of an
// undirected, weighted graph using Union-Find for cycle detection.
//
// Input: "edges.txt"
// Format:
//   Line 1: <number_of_vertices> <number_of_edges>
//   Remaining lines: <node1> <node2> <edge_weight>
//
// Output: Total cost of the MST
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge>> G;  // edge list (weight, (u, v))
    vector<pair<int, edge>> T;  // MST edges
    int* parent;
    int* rank;
    int V;

public:
    Graph(int V);
    ~Graph();
    void addEdge(int u, int v, int w);
    int find(int i);
    void Union(int u, int v);
    void kruskal();
    long long cost();
};

Graph::Graph(int V) : V(V) {
    parent = new int[V];
    rank = new int[V];
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
    G.clear();
    T.clear();
}

Graph::~Graph() {
    delete[] parent;
    delete[] rank;
}

void Graph::addEdge(int u, int v, int w) {
    G.emplace_back(w, edge(u, v));
}

int Graph::find(int i) {
    if (parent[i] != i)
        parent[i] = find(parent[i]);  // Path compression
    return parent[i];
}

void Graph::Union(int u, int v) {
    int ru = find(u);
    int rv = find(v);
    if (ru == rv) return;

    if (rank[ru] > rank[rv]) parent[rv] = ru;
    else if (rank[rv] > rank[ru]) parent[ru] = rv;
    else {
        parent[rv] = ru;
        rank[ru]++;
    }
}

void Graph::kruskal() {
    sort(G.begin(), G.end());  // Sort edges by weight
    for (const auto& e : G) {
        int u = e.second.first;
        int v = e.second.second;
        if (find(u) != find(v)) {
            T.push_back(e);     // Add edge to MST
            Union(u, v);        // Union their sets
        }
    }
}

long long Graph::cost() {
    long long total = 0;
    for (const auto& e : T) {
        total += e.first;
    }
    return total;
}

int main() {
    int V, E;
    ifstream file("edges.txt");
    file >> V >> E;

    Graph g(V);
    int u, v, wt;
    while (file >> u >> v >> wt) {
        g.addEdge(u - 1, v - 1, wt);  // zero-indexed
    }

    g.kruskal();
    cout << "Total cost of MST (Kruskal's): " << g.cost() << endl;
    // Expected: -3612829
    return 0;
}
