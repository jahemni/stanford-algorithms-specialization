// floyd_warshall_apsp.cpp
// ------------------------------------------------------------------------
// Computes all-pairs shortest paths using the Floyd-Warshall algorithm.
// Handles graphs with negative edge weights and detects negative cycles.
//
// Input: "g3.txt"
// Format:
//   Line 1: <V> <E> (vertices, edges)
//   Next E lines: <src> <dst> <weight> (1-based index)
//
// Output:
//   Minimum shortest path among all pairs or report negative cycle
//
// Course: Stanford Algorithms Specialization - Course 4, Week 3
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;

const int V = 1000; // Maximum number of vertices (can adjust based on input)

void floydWarshall(int dist[V][V], int v) {
    // Core triple loop
    for (int k = 0; k < v; ++k) {
        for (int i = 0; i < v; ++i) {
            for (int j = 0; j < v; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < v; ++i) {
        if (dist[i][i] < 0) {
            cout << "Negative cycle detected." << endl;
            return;
        }
    }

    // Find minimum shortest-path value across all pairs
    int minPath = INT_MAX;
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            if (i != j && dist[i][j] < minPath) {
                minPath = dist[i][j];
            }
        }
    }

    cout << "Minimum shortest path among all pairs: " << minPath << endl;
}

int main() {
    int v, e;
    ifstream file("g3.txt");
    file >> v >> e;

    // Initialize distance matrix
    int dist[V][V];
    for (int i = 0; i < v; ++i) {
        for (int j = 0; j < v; ++j) {
            if (i == j) dist[i][j] = 0;
            else dist[i][j] = INT_MAX;
        }
    }

    // Read edges (1-indexed to 0-indexed)
    int src, dst, wt;
    while (file >> src >> dst >> wt) {
        dist[src - 1][dst - 1] = wt;
    }

    floydWarshall(dist, v);
    return 0;
}
