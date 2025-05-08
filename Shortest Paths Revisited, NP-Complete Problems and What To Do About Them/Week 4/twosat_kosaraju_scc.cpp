// twosat_kosaraju_scc.cpp
// ------------------------------------------------------------------------
// Solves the 2-Satisfiability (2-SAT) problem using Kosaraju's algorithm
// to detect strongly connected components (SCCs) in the implication graph.
//
// Input: "2satX.txt"
// Format:
//   Line 1: number of variables n
//   Next lines: each clause (a ∨ b), where a and b can be negative
//
// Output:
//   "Satisfiable" or "Unsatisfiable"
//
// Course: Stanford Algorithms Specialization - Course 4, Week 4
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

const int MAX = 2000001;

vector<int> adj[MAX], adjInv[MAX];
bool visited[MAX], visitedInv[MAX];
int scc[MAX];
stack<int> s;

int n, a, b;
int counter = 1;

void addEdge(int u, int v) {
    adj[u].push_back(v);
    adjInv[v].push_back(u);
}

void dfs(int u) {
    visited[u] = true;
    for (int v : adj[u]) {
        if (!visited[v]) dfs(v);
    }
    s.push(u);
}

void dfsInv(int u) {
    visitedInv[u] = true;
    scc[u] = counter;
    for (int v : adjInv[u]) {
        if (!visitedInv[v]) dfsInv(v);
    }
}

int main() {
    ifstream file("2sat6.txt");
    file >> n;

    while (file >> a >> b) {
        // Map: x  → x, ¬x → x+n
        if (a > 0 && b > 0) {
            addEdge(a + n, b);
            addEdge(b + n, a);
        } else if (a > 0 && b < 0) {
            addEdge(a + n, -b + n);
            addEdge(-b, a);
        } else if (a < 0 && b > 0) {
            addEdge(-a, b);
            addEdge(b + n, -a + n);
        } else { // a < 0 && b < 0
            addEdge(-a, -b + n);
            addEdge(-b, -a + n);
        }
    }

    // First pass: DFS on original graph
    for (int i = 1; i <= 2 * n; ++i) {
        if (!visited[i]) dfs(i);
    }

    // Second pass: DFS on transposed graph
    while (!s.empty()) {
        int node = s.top(); s.pop();
        if (!visitedInv[node]) {
            dfsInv(node);
            counter++;
        }
    }

    // Check for satisfiability
    for (int i = 1; i <= n; ++i) {
        if (scc[i] == scc[i + n]) {
            cout << "Unsatisfiable" << endl;
            return 0;
        }
    }

    cout << "Satisfiable" << endl;
    return 0;
}
