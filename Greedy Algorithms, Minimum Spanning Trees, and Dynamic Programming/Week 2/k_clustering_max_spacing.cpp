// k_clustering_max_spacing.cpp
// --------------------------------------------------------------------
// Clustering using Kruskal’s Algorithm to compute the maximum spacing
// of a k-clustering. The algorithm uses union-find to maintain sets.
//
// Input: "clustering1.txt"
// Format:
//   Line 1: <number_of_nodes>
//   Remaining lines: <node1> <node2> <edge_weight>
//
// Output: Maximum spacing between the resulting k clusters
//
// Course: Stanford Algorithms Specialization - Course 3, Week 2
// --------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

#define edge pair<int, int>

class Graph {
private:
    vector<pair<int, edge>> edges; // (weight, (u, v))
    vector<int> parent, rank;
    int V;

public:
    Graph(int V) : V(V) {
        parent.resize(V);
        rank.resize(V, 0);
        for (int i = 0; i < V; ++i) parent[i] = i;
    }

    void addEdge(int u, int v, int w) {
        edges.push_back({w, {u, v}});
    }

    int find(int i) {
        if (parent[i] != i)
            parent[i] = find(parent[i]); // path compression
        return parent[i];
    }

    void Union(int u, int v) {
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

    int maxSpacingClustering(int k) {
        sort(edges.begin(), edges.end());
        int clusters = V;
        int i = 0;

        while (clusters > k) {
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            if (find(u) != find(v)) {
                Union(u, v);
                clusters--;
            }
            i++;
        }

        // Find the smallest edge connecting two separate clusters
        while (i < edges.size()) {
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            if (find(u) != find(v)) {
                return edges[i].first;  // maximum spacing
            }
            i++;
        }

        return -1; // fallback
    }
};

int main() {
    int V;
    ifstream file("clustering1.txt");
    file >> V;

    Graph g(V);
    int u, v, w;
    while (file >> u >> v >> w) {
        g.addEdge(u - 1, v - 1, w); // zero-indexed
    }

    int k = 4;
    int spacing = g.maxSpacingClustering(k);
    cout << "Maximum spacing of " << k << "-clustering: " << spacing << endl;
    // Expected: 106
}
