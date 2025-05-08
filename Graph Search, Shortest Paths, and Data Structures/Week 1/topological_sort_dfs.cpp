// topological_sort_dfs.cpp
// --------------------------------------------------------------------
// Perform Topological Sort on a Directed Acyclic Graph (DAG) using DFS.
//
// Vertices are pushed to a stack in post-order; popping the stack
// yields the topological order of tasks/nodes.
//
// This is useful in dependency resolution, scheduling, and compilers.
// --------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Add a directed edge from s to d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
}

// DFS with post-order stacking
void DFS(vector<int> adj[], int v, vector<bool> &visited, stack<int> &order) {
    visited[v] = true;

    for (int neighbor : adj[v]) {
        if (!visited[neighbor]) {
            DFS(adj, neighbor, visited, order);
        }
    }

    order.push(v); // push after exploring all descendants
}

int main() {
    const int V = 6;
    vector<int> adj[V];

    // Construct the DAG
    addEdge(adj, 4, 2);
    addEdge(adj, 5, 1);
    addEdge(adj, 4, 0);
    addEdge(adj, 3, 1);
    addEdge(adj, 1, 3);  // introduces a cycle (optional to remove)
    addEdge(adj, 3, 2);

    vector<bool> visited(V, false);
    stack<int> order;

    // Call DFS for unvisited vertices
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            DFS(adj, i, visited, order);
        }
    }

    // Output topological order
    cout << "Topological Sort (DFS-based):\n";
    while (!order.empty()) {
        cout << order.top() << " ";
        order.pop();
    }
    cout << endl;

    return 0;
}
