// karger_min_cut.cpp
// ------------------------------------------------------------------
// Problem: Find the Minimum Cut of an undirected graph using
// Karger's Randomized Contraction Algorithm (Monte Carlo method).
//
// This program reads a graph from "kargerMinCut.txt", repeatedly
// applies the contraction algorithm, and outputs the smallest cut
// found over multiple iterations.
//
// This is based on the Week 4 assignment from Stanford's
// Algorithms Specialization on Coursera.
// ------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Edge {
    int src, dest;
};

struct Graph {
    int V, E;
    Edge* edge;
};

struct Subset {
    int parent;
    int rank;
};

// Disjoint Set (Union-Find) - Find with path compression
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

// Union by rank
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Perform Karger's Random Contraction Algorithm once
int randomContraction(Graph* graph) {
    int V = graph->V;
    int E = graph->E;
    Edge* edge = graph->edge;

    Subset* subsets = new Subset[V];
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int remainingVertices = V;

    while (remainingVertices > 2) {
        int i = rand() % E;

        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);

        if (subset1 != subset2) {
            Union(subsets, subset1, subset2);
            remainingVertices--;
        }
    }

    int cutEdges = 0;
    for (int i = 0; i < E; i++) {
        int subset1 = find(subsets, edge[i].src);
        int subset2 = find(subsets, edge[i].dest);
        if (subset1 != subset2) {
            cutEdges++;
        }
    }

    delete[] subsets;
    return cutEdges;
}

// Create an empty graph with V vertices and E edges
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[E];
    return graph;
}

int main() {
    srand(static_cast<unsigned>(time(NULL)));

    const int V = 200;
    ifstream file("kargerMinCut.txt");

    // First pass to count unique edges
    string line;
    int E = 0;
    while (getline(file, line)) {
        istringstream iss(line);
        int src, dest;
        iss >> src;
        while (iss >> dest) {
            if (dest > src) E++;  // Avoid double-counting
        }
    }
    file.close();

    // Create and populate the graph
    Graph* graph = createGraph(V, E);
    ifstream file2("kargerMinCut.txt");
    int edgeCount = 0;
    while (getline(file2, line)) {
        istringstream iss(line);
        int src, dest;
        iss >> src;
        while (iss >> dest) {
            if (dest > src) {
                graph->edge[edgeCount].src = src - 1;  // zero-indexed
                graph->edge[edgeCount].dest = dest - 1;
                edgeCount++;
            }
        }
    }
    file2.close();

    // Run the algorithm multiple times to improve probability of correctness
    int minCut = INT_MAX;
    const int trials = 200;
    for (int i = 0; i < trials; i++) {
        int currentCut = randomContraction(graph);
        minCut = min(minCut, currentCut);
    }

    cout << "Estimated Minimum Cut: " << minCut << endl;

    delete[] graph->edge;
    delete graph;

    return 0;
}
