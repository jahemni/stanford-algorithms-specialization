// bfs_shortest_path.cpp
// --------------------------------------------------------------------
// Find the shortest path in an unweighted undirected graph using BFS.
// Also reconstructs and prints the actual path from source to destination.
//
// Suitable for use in scenarios where edge weights are uniform (e.g., 1).
// --------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Add an undirected edge between s and d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
    adj[d].push_back(s);
}

// Perform BFS to compute distances and predecessors
void BFS(vector<int> adj[], int s, int V, vector<int>& dist, vector<int>& prev) {
    vector<bool> visited(V, false);
    queue<int> Q;

    visited[s] = true;
    dist[s] = 0;
    Q.push(s);

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();
        cout << v << " ";

        for (int neighbor : adj[v]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                dist[neighbor] = dist[v] + 1;
                prev[neighbor] = v;
                Q.push(neighbor);
            }
        }
    }
}

// Print the shortest path from s to d using BFS results
void printPath(vector<int> adj[], int s, int V, int d) {
    vector<int> dist(V, -1);
    vector<int> prev(V, -1);

    cout << "BFS Traversal from node " << s << ":\n";
    BFS(adj, s, V, dist, prev);
    cout << "\n\nShortest distance from " << s << " to " << d << ": " << dist[d] << endl;

    // Reconstruct path
    vector<int> path;
    for (int at = d; at != -1; at = prev[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
}

int main() {
    const int V = 8;
    vector<int> adj[V];

    // Construct graph
    addEdge(adj, 0, 1);
    addEdge(adj, 0, 3);
    addEdge(adj, 1, 2);
    addEdge(adj, 3, 4);
    addEdge(adj, 3, 7);
    addEdge(adj, 4, 5);
    addEdge(adj, 4, 6);
    addEdge(adj, 4, 7);
    addEdge(adj, 5, 6);
    addEdge(adj, 6, 7);

    // Find and print path from 0 to 7
    printPath(adj, 0, V, 7);

    return 0;
}
