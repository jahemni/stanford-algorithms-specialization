// kosaraju_scc.cpp
// ---------------------------------------------------------------------
// Problem: Find the sizes of the five largest Strongly Connected Components (SCCs)
// in a large directed graph using Kosaraju's Two-Pass Algorithm.
//
// This implementation reads input from "SCC.txt" and outputs the top 5 SCC sizes.
// It uses DFS on the original and reversed graphs, leveraging finishing times.
//
// Course: Stanford Algorithms Specialization - Course 2, Week 1
// ---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

// Add a directed edge from s to d
void addEdge(vector<int> adj[], int s, int d) {
    adj[s].push_back(d);
}

// Perform DFS on original graph to compute finishing times
void DFS(vector<int> adj[], int node, vector<bool> &visited, stack<int> &finishStack) {
    visited[node] = true;
    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            DFS(adj, neighbor, visited, finishStack);
        }
    }
    finishStack.push(node);
}

// Perform DFS on reversed graph to compute SCC size
int DFS_Reverse(vector<int> adjRev[], int node, vector<bool> &visited) {
    visited[node] = true;
    int size = 1;
    for (int neighbor : adjRev[node]) {
        if (!visited[neighbor]) {
            size += DFS_Reverse(adjRev, neighbor, visited);
        }
    }
    return size;
}

int main() {
    const int V = 875714;
    vector<int> graph[V];
    vector<int> reverseGraph[V];

    // To test locally, replace with "SCC_small.txt" and V = 3200
    ifstream file("SCC.txt");
    int src, dest;

    while (file >> src >> dest) {
        addEdge(graph, src - 1, dest - 1);         // Original graph
        addEdge(reverseGraph, dest - 1, src - 1);  // Reversed graph
    }

    // First pass: DFS on original graph to compute finishing times
    stack<int> finishStack;
    vector<bool> visited(V, false);

    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            DFS(graph, i, visited, finishStack);
        }
    }

    // Second pass: DFS on reversed graph in finishing time order
    fill(visited.begin(), visited.end(), false);
    priority_queue<int> topSCCs;

    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();

        if (!visited[node]) {
            int sccSize = DFS_Reverse(reverseGraph, node, visited);
            topSCCs.push(sccSize);
        }
    }

    // Output top 5 SCC sizes (descending)
    cout << "Top 5 SCC sizes:" << endl;
    for (int i = 0; i < 5; ++i) {
        if (!topSCCs.empty()) {
            cout << topSCCs.top() << (i < 4 ? ", " : "\n");
            topSCCs.pop();
        } else {
            cout << "0" << (i < 4 ? ", " : "\n");  // Pad with 0s if fewer than 5 SCCs
        }
    }

    return 0;
}
