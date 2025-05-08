// prim_mst_matrix.cpp
// ---------------------------------------------------------------------
// Compute the Minimum Spanning Tree (MST) of a graph using Prim’s algorithm.
//
// Graph is represented as an adjacency matrix. At each step, the algorithm
// adds the minimum weight edge connecting an unvisited vertex to the MST.
//
// Input: "edges.txt"
// Format:
//   Line 1: <# vertices> <# edges>
//   Remaining lines: <node1> <node2> <edge_weight>
//
// Output: Total cost of the MST
//
// Course: Stanford Algorithms Specialization - Course 3, Week 1
// ---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <cstring>

using namespace std;

// Select the unvisited vertex with the minimum edge weight
int findMinVertex(const vector<int>& value, const vector<bool>& visited, int V) {
    int minVal = INT_MAX;
    int vertex = -1;
    for (int i = 0; i < V; ++i) {
        if (!visited[i] && value[i] < minVal) {
            minVal = value[i];
            vertex = i;
        }
    }
    return vertex;
}

int main() {
    int V, E;
    ifstream file("edges.txt");
    file >> V >> E;

    int graph[V][V];
    memset(graph, 0, sizeof(graph));

    int a, b, wt;
    while (file >> a >> b >> wt) {
        graph[a - 1][b - 1] = wt;
        graph[b - 1][a - 1] = wt;
    }

    vector<bool> visited(V, false);
    vector<int> value(V, INT_MAX);
    vector<int> parent(V, -1);

    value[0] = 0; // Start from node 0

    for (int i = 0; i < V - 1; ++i) {
        int u = findMinVertex(value, visited, V);
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !visited[v] && graph[u][v] < value[v]) {
                value[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    long long totalCost = 0;
    for (int i = 1; i < V; ++i) {
        totalCost += graph[i][parent[i]];
    }

    cout << "Total cost of Minimum Spanning Tree: " << totalCost << endl;
    // Expected output: -3612829

    return 0;
}
