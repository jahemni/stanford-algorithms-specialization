// dijkstra_matrix.cpp
// --------------------------------------------------------------------
// Dijkstra's Algorithm implementation using an adjacency matrix.
//
// Reads input from "dijkstraData.txt" and computes the shortest distances
// from source node 0 to a predefined list of target vertices.
//
// This is a basic version using O(V^2) complexity, suitable for small graphs.
// --------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <climits>
#include <string>

using namespace std;

#define V 200  // Number of vertices

// Select the unvisited vertex with the smallest distance
int selectMinVertex(int shortestDist[], bool visited[]) {
    int minDist = INT_MAX, index = -1;
    for (int i = 0; i < V; ++i) {
        if (!visited[i] && shortestDist[i] <= minDist) {
            minDist = shortestDist[i];
            index = i;
        }
    }
    return index;
}

// Dijkstra's Algorithm using adjacency matrix
void dijkstra(int adj[V][V], int src) {
    bool visited[V] = {false};
    int shortestDist[V];

    // Initialize distances
    for (int i = 0; i < V; ++i) {
        shortestDist[i] = INT_MAX;
    }
    shortestDist[src] = 0;

    // Main loop
    for (int count = 0; count < V - 1; ++count) {
        int u = selectMinVertex(shortestDist, visited);
        if (u == -1) break;  // Unreachable vertices
        visited[u] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && adj[u][v] > 0 &&
                shortestDist[u] != INT_MAX &&
                shortestDist[u] + adj[u][v] < shortestDist[v]) {
                shortestDist[v] = shortestDist[u] + adj[u][v];
            }
        }
    }

    // Output distances to specific target nodes
    int targets[] = {7, 37, 59, 82, 99, 115, 133, 165, 188, 197};
    cout << "Shortest distances from vertex 0 to targets:\n";
    for (int i = 0; i < 10; ++i) {
        int node = targets[i] - 1;
        cout << shortestDist[node] << (i < 9 ? "," : "\n");
    }
}

int main() {
    int adj[V][V] = {0};
    ifstream file("dijkstraData.txt");
    string line;

    // Parse adjacency matrix from file
    while (getline(file, line)) {
        istringstream iss(line);
        int src;
        iss >> src;
        string token;
        while (iss >> token) {
            size_t pos = token.find(',');
            int dest = stoi(token.substr(0, pos));
            int length = stoi(token.substr(pos + 1));
            adj[src - 1][dest - 1] = length;
        }
    }

    dijkstra(adj, 0);
    return 0;
}
