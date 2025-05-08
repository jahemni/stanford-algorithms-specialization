// dfs_traversal_demo.cpp
// -------------------------------------------------------------------
// Demonstration of Depth-First Search (DFS) on a directed graph.
// The program performs DFS starting from node 2 and prints the
// traversal order.
//
// Useful for understanding how DFS recursively explores paths.
// -------------------------------------------------------------------

#include <iostream>
#include <vector>

using namespace std;

// Add a directed edge from s to d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
}

// Perform DFS starting from node s
void DFS(vector<int> adj[], int s, vector<bool> &visited) {
    visited[s] = true;
    cout << s << " ";

    for (int neighbor : adj[s]) {
        if (!visited[neighbor]) {
            DFS(adj, neighbor, visited);
        }
    }
}

int main() {
    const int V = 4;
    vector<int> adj[V];

    // Construct a directed graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 0);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 3);

    vector<bool> visited(V, false);

    cout << "DFS traversal starting from vertex 2:\n";
    DFS(adj, 2, visited);
    cout << endl;

    return 0;
}
