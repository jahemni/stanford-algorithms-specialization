// undirected_graph_demo.cpp
// ------------------------------------------------------------------
// Demonstration of an undirected graph using adjacency lists
// implemented with vector<int>.
//
// This program builds a small graph and prints its adjacency list.
// ------------------------------------------------------------------

#include <iostream>
#include <vector>

using namespace std;

// Add an undirected edge between vertex s and d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
    adj[d].push_back(s);
}

// Print the adjacency list of the graph
void printGraph(const vector<int> adj[], int V) {
    for (int v = 0; v < V; ++v) {
        cout << "Vertex " << v << ":";
        for (int neighbor : adj[v]) {
            cout << " -> " << neighbor;
        }
        cout << endl;
    }
}

int main() {
    const int V = 5;  // Number of vertices
    vector<int> adj[V];

    // Add edges (undirected)
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 0, 3);
    addEdge(adj, 1, 2);

    // Print the graph
    cout << "Adjacency List of the Graph:\n";
    printGraph(adj, V);

    return 0;
}
