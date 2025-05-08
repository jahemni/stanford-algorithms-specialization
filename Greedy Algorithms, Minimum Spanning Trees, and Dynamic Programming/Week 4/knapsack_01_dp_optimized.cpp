// knapsack_01_dp_optimized.cpp
// ------------------------------------------------------------------------
// Solves the 0/1 Knapsack Problem using space-optimized dynamic programming.
// Suitable for large capacities where a full DP table would exceed memory.
//
// Input: "knapsack_big.txt"
// Format:
//   Line 1: <W> <n>  (max weight, number of items)
//   Next n lines: <value> <weight> per item
//
// Output:
//   Maximum total value achievable with weight ≤ W
//
// Course: Stanford Algorithms Specialization - Course 3, Week 4
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int W, n;
    ifstream file("knapsack_big.txt");
    file >> W >> n;

    vector<pair<int, int>> items;  // (value, weight)
    int value, weight;
    while (file >> value >> weight) {
        items.emplace_back(value, weight);
    }

    // Only two rows needed for optimization
    vector<long long> prev(W + 1, 0);
    vector<long long> curr(W + 1, 0);

    for (int i = 1; i <= n; ++i) {
        int vi = items[i - 1].first;
        int wi = items[i - 1].second;

        for (int w = 0; w <= W; ++w) {
            if (wi > w) {
                curr[w] = prev[w];
            } else {
                curr[w] = max(prev[w], prev[w - wi] + vi);
            }
        }

        // Swap current row into previous and reset current
        swap(prev, curr);
        fill(curr.begin(), curr.end(), 0);
    }

    cout << "Maximum value achievable: " << prev[W] << endl;
    // Expected output: 4243395

    return 0;
}
