// tsp_bitmask_dp.cpp
// ------------------------------------------------------------------------
// Solves the Traveling Salesman Problem (TSP) using dynamic programming
// with bitmasking to track visited cities. This is exponential (O(n * 2^n))
// but optimized compared to naive permutation-based methods.
//
// Input: "tsp.txt"
// Format:
//   Line 1: <number of cities>
//   Next lines: <x> <y> coordinates of each city
//
// Output:
//   Minimum cost to complete the TSP tour (starting and ending at node 0)
//
// Course: Stanford Algorithms Specialization - Course 4, Week 2
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <limits>
#include <cstring>

using namespace std;

const int N = 25;
const double INF = numeric_limits<double>::infinity();

int VISITED_ALL;
double dist[N][N];
double dp[1 << N][N];  // memoization table: dp[mask][i] = min cost to reach i with visited mask

int cities;

double tsp(int mask, int pos) {
    if (mask == VISITED_ALL)
        return dist[pos][0];  // return to start

    if (dp[mask][pos] != -1)
        return dp[mask][pos];

    double ans = INF;

    for (int city = 0; city < cities; ++city) {
        if ((mask & (1 << city)) == 0) {
            double newAns = dist[pos][city] + tsp(mask | (1 << city), city);
            ans = min(ans, newAns);
        }
    }

    return dp[mask][pos] = ans;
}

int main() {
    ifstream file("tsp.txt");
    file >> cities;

    VISITED_ALL = (1 << cities) - 1;

    vector<pair<double, double>> coords(cities);
    for (int i = 0; i < cities; ++i) {
        double x, y;
        file >> x >> y;
        coords[i] = {x, y};
    }

    // Compute pairwise Euclidean distances
    for (int i = 0; i < cities; ++i) {
        for (int j = 0; j < cities; ++j) {
            if (i == j) dist[i][j] = 0;
            else {
                double dx = coords[i].first - coords[j].first;
                double dy = coords[i].second - coords[j].second;
                dist[i][j] = sqrt(dx * dx + dy * dy);
            }
        }
    }

    // Initialize DP table with -1 (unvisited state)
    memset(dp, -1, sizeof(dp));

    double result = tsp(1, 0);  // Start from city 0, only it visited
    cout << "Minimum TSP tour cost: " << result << endl;

    return 0;
}
