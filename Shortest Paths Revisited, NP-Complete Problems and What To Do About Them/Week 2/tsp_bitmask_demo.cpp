// tsp_bitmask_demo.cpp
// ------------------------------------------------------------------------
// Demonstrates TSP using recursive bitmask DP on a small hardcoded graph.
//
// This is a compact example to verify correctness and understand how
// subset masks and state transitions work in the TSP DP solution.
//
// Output: Minimum TSP tour cost for the 4-city problem
// ------------------------------------------------------------------------

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

const int N = 4;
const int VISITED_ALL = (1 << N) - 1;

// Recursive DP (no memoization for demo clarity)
int tsp(int dist[N][N], int mask, int pos) {
    if (mask == VISITED_ALL) {
        return dist[pos][0];  // return to starting city
    }

    int ans = INT_MAX;

    for (int city = 0; city < N; ++city) {
        if ((mask & (1 << city)) == 0) {
            int newCost = dist[pos][city] + tsp(dist, mask | (1 << city), city);
            ans = min(ans, newCost);
        }
    }

    return ans;
}

int main() {
    int dist[N][N] = {
        {0, 20, 42, 25},
        {20, 0, 30, 34},
        {42, 30, 0, 10},
        {25, 34, 10, 0}
    };

    int result = tsp(dist, 1, 0);  // start at city 0 with only it visited
    cout << "Minimum TSP tour cost: " << result << endl;  // Expected: 85

    return 0;
}
