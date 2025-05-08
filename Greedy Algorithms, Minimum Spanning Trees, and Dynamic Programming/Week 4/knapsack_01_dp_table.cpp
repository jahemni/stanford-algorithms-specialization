// knapsack_01_dp_table.cpp
// ------------------------------------------------------------------------
// Solves the 0/1 Knapsack Problem using a 2D bottom-up dynamic programming table.
//
// Input: "knapsack1.txt"
// Format:
//   Line 1: <W> <n>  (max weight, number of items)
//   Next n lines: <value> <weight> for each item
//
// Output:
//   Maximum total value achievable with weight ≤ W
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int W, n;
    ifstream file("knapsack1.txt");
    file >> W >> n;

    vector<pair<int, int>> items; // (value, weight)
    int value, weight;
    while (file >> value >> weight) {
        items.emplace_back(value, weight);
    }

    // DP table: arr[i][w] = max value using first i items and total weight ≤ w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int vi = items[i - 1].first;
        int wi = items[i - 1].second;
        for (int w = 0; w <= W; ++w) {
            if (wi > w) {
                dp[i][w] = dp[i - 1][w]; // cannot include item i
            } else {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - wi] + vi);
            }
        }
    }

    cout << "Maximum value achievable: " << dp[n][W] << endl;
    // Expected: 2493893

    return 0;
}
