// floyd_warshall_demo.cpp
// ------------------------------------------------------------------------
// Demonstration of the Floyd-Warshall algorithm on a hardcoded graph.
// Computes all-pairs shortest paths and prints full distance matrix.
//
// Detects negative-weight cycles and prints distances for verification.
//
// Course: Stanford Algorithms Specialization - Course 4, Week 3
// ------------------------------------------------------------------------

#include <iostream>
#include <climits>
using namespace std;

const int V = 6;

void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Initialize distance matrix
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            dist[i][j] = graph[i][j];

    // Core Floyd-Warshall loop
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Check for negative-weight cycle
    for (int i = 0; i < V; ++i) {
        if (dist[i][i] < 0) {
            cout << "Negative edge cycle detected.\n";
            return;
        }
    }

    // Print the distance matrix
    cout << "All-pairs shortest path distances:\n";
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (dist[i][j] == INT_MAX)
                cout << "INF\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

int main() {
    int graph[V][V] = {
        {0, 1, 4, INT_MAX, INT_MAX, INT_MAX},
        {INT_MAX, 0, 4, 2, 7, INT_MAX},
        {INT_MAX, INT_MAX, 0, 3, 4, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, 0, INT_MAX, 4},
        {INT_MAX, INT_MAX, INT_MAX, 3, 0, INT_MAX},
        {INT_MAX, INT_MAX, INT_MAX, INT_MAX, 5, 0}
    };

    floydWarshall(graph);
    return 0;
}
