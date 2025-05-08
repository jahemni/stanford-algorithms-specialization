// bfs_connected_components.cpp
// ------------------------------------------------------------------------
// Identify and print connected components in an undirected graph using BFS.
// A BFS is started from each unvisited node to discover its component.
//
// This approach is useful in unconnected graphs where multiple BFS runs
// are required to cover all nodes.
// ------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Add an undirected edge between s and d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
    adj[d].push_back(s);
}

// Perform BFS from source node s
void BFS(vector<int> adj[], int s, vector<bool> &visited) {
    queue<int> Q;
    Q.push(s);
    visited[s] = true;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                Q.push(neighbor);
            }
        }
    }
    cout << endl;
}

int main() {
    const int V = 5;
    vector<int> adj[V];

    // Construct an undirected graph with two disconnected components
    addEdge(adj, 0, 1);  // Component 1: 0-1
    addEdge(adj, 2, 3);  // Component 2: 2-3-4
    addEdge(adj, 3, 4);

    vector<bool> visited(V, false);

    cout << "Connected components (using BFS):\n";
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            BFS(adj, i, visited);
        }
    }

    return 0;
}
