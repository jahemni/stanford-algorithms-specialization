// tsp_nearest_neighbor.cpp
// ------------------------------------------------------------------------
// Solves the Traveling Salesman Problem approximately using the
// Nearest Neighbor Heuristic (NNH). This is a greedy approach:
// 
// 1. Start at the first city
// 2. At each step, visit the closest unvisited city
// 3. Return to the starting city when all have been visited
//
// Input: "nn.txt"
// Format:
//   Line 1: number of cities (n)
//   Next n lines: <index> <x> <y> coordinates (1-based index)
//
// Output: Total tour distance (double precision)
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cfloat>

using namespace std;

int main() {
    int n;
    ifstream file("nn.txt");
    file >> n;

    vector<pair<double, double>> cities(n);  // (x, y) for each city
    int index;
    double x, y;
    for (int i = 0; i < n; ++i) {
        file >> index >> x >> y;
        cities[i] = {x, y};
    }

    vector<bool> visited(n, false);
    visited[0] = true;
    int current = 0;
    int visitedCount = 1;
    double totalDist = 0.0;

    while (visitedCount < n) {
        double nearest = DBL_MAX;
        int nextCity = -1;

        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                double dx = cities[current].first - cities[i].first;
                double dy = cities[current].second - cities[i].second;
                double dist = sqrt(dx * dx + dy * dy);

                // Break ties by smaller index
                if (dist < nearest || (fabs(dist - nearest) < 1e-9 && i < nextCity)) {
                    nearest = dist;
                    nextCity = i;
                }
            }
        }

        visited[nextCity] = true;
        totalDist += nearest;
        current = nextCity;
        ++visitedCount;

        if (visitedCount % 100 == 0) {
            cout << "Visited " << visitedCount << " cities..." << endl;
        }
    }

    // Return to start city
    double dx = cities[current].first - cities[0].first;
    double dy = cities[current].second - cities[0].second;
    totalDist += sqrt(dx * dx + dy * dy);

    cout << fixed;
    cout << "Total tour distance (nearest neighbor): " << totalDist << endl;

    return 0;
}
