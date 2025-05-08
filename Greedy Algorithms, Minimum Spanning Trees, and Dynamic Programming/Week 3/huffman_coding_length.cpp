// huffman_coding_length.cpp
// ----------------------------------------------------------------------
// Computes the maximum and minimum codeword lengths resulting from
// Huffman's algorithm applied to a set of symbol weights.
//
// Input: "huffman.txt"
// Format:
//   Line 1: number of symbols (n)
//   Next n lines: weights of symbols
//
// Output:
//   Max codeword length
//   Min codeword length
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
using pi = pair<int, int>;  // (weight, depth)

int main() {
    int n;
    ifstream file("huffman.txt");
    file >> n;

    // Min-heap: (weight, depth)
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    int w;
    while (file >> w) {
        pq.push({w, 0});
    }

    int minDepth = INT_MAX;
    int maxDepth = 0;

    while (pq.size() > 1) {
        auto [w1, d1] = pq.top(); pq.pop();
        auto [w2, d2] = pq.top(); pq.pop();

        int mergedWeight = w1 + w2;
        int mergedDepth = max(d1, d2) + 1;
        pq.push({mergedWeight, mergedDepth});

        // Track minimum depth when a leaf node merges
        if (d1 == 0 || d2 == 0) {
            minDepth = min(minDepth, mergedDepth);
        }
        maxDepth = mergedDepth;
    }

    cout << "Maximum codeword length: " << maxDepth << endl;
    cout << "Minimum codeword length: " << minDepth << endl;
    // Expected: Max = 19
}
