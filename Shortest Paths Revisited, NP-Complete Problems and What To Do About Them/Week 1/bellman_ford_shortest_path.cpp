// bellman_ford_shortest_path.cpp
// ------------------------------------------------------------------------
// Computes single-source shortest paths using the Bellman-Ford algorithm.
// Handles graphs with negative edge weights and detects negative cycles.
//
// Input:
//   Line 1: <V> <E> (number of vertices and edges)
//   Next E lines: <src> <dst> <weight>
//
// Output:
//   Shortest distances from source (node 0) or report negative cycle.
//
// Course: Stanford Algorithms Specialization - Course 4, Week 1
// ------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

struct Edge {
    int src, dst, wt;
};

int V, E;

void bellmanFord(vector<Edge>& edges) {
    vector<int> distance(V, INT_MAX);
    distance[0] = 0;  // Assume source node is 0

    bool updated = false;

    // Relax all edges (V - 1) times
    for (int i = 0; i < V - 1; ++i) {
        updated = false;
        for (const Edge& e : edges) {
            if (distance[e.src] != INT_MAX && distance[e.src] + e.wt < distance[e.dst]) {
                distance[e.dst] = distance[e.src] + e.wt;
                updated = true;
            }
        }
        if (!updated) break;  // Early stopping
    }

    // Check for negative-weight cycle
    for (const Edge& e : edges) {
        if (distance[e.src] != INT_MAX && distance[e.src] + e.wt < distance[e.dst]) {
            cout << "Graph contains a negative-weight cycle." << endl;
            return;
        }
    }

    // Print shortest distances
    cout << "Shortest distances from source node 0:\n";
    for (int i = 0; i < V; ++i) {
        if (distance[i] == INT_MAX)
            cout << "Node " << i << ": INF" << endl;
        else
            cout << "Node " << i << ": " << distance[i] << endl;
    }
}

int main() {
    cin >> V >> E;
    vector<Edge> edges(E);

    for (int i = 0; i < E; ++i) {
        cin >> edges[i].src >> edges[i].dst >> edges[i].wt;
    }

    bellmanFord(edges);
    return 0;
}
