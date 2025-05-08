// bfs_traversal_demo.cpp
// --------------------------------------------------------------------
// Demonstration of Breadth-First Search (BFS) traversal in a directed graph.
// This example constructs a graph with 4 vertices and performs BFS from node 2.
//
// Useful for visualizing BFS behavior and verifying traversal order.
// --------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Add a directed edge from vertex s to vertex d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
}

// Perform BFS from source vertex s
void BFS(const vector<int> adj[], int s, int V) {
    vector<bool> visited(V, false);
    queue<int> Q;

    visited[s] = true;
    Q.push(s);

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
    const int V = 4;
    vector<int> adj[V];

    // Construct graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 2);
    addEdge(adj, 2, 0);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 3);

    cout << "BFS traversal starting from vertex 2:\n";
    BFS(adj, 2, V);

    return 0;
}
