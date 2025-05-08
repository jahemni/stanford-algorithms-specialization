// mwis_path_dp.cpp
// ------------------------------------------------------------------------
// Solves the Maximum Weight Independent Set (MWIS) problem for a path graph
// using dynamic programming. Then reconstructs the solution and checks
// for the inclusion of specific vertices.
//
// Input: "mwis.txt"
// Format:
//   Line 1: number of vertices (n)
//   Next n lines: weight of vertex i (1-indexed)
//
// Output:
//   List of included vertex indices and encoded bitstring (e.g., 10100110)
//
// Course: Stanford Algorithms Specialization - Course 3, Week 4
// ------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int n;
    ifstream file("mwis.txt");
    file >> n;

    vector<int> weight(n + 1);
    for (int i = 1; i <= n; ++i) {
        file >> weight[i];
    }

    // DP array: arr[i] = max weight of MWIS from vertex 1 to i
    vector<long long> arr(n + 1, 0);
    arr[0] = 0;
    arr[1] = weight[1];

    for (int j = 2; j <= n; ++j) {
        arr[j] = max(arr[j - 1], arr[j - 2] + weight[j]);
    }

    // Reconstruct the solution
    set<int> included;
    int i = n;
    while (i >= 2) {
        if (arr[i - 1] >= arr[i - 2] + weight[i]) {
            i--;
        } else {
            included.insert(i);
            i -= 2;
        }
    }
    if (i == 1 && arr[1] == weight[1]) {
        included.insert(1);
    }

    // Optional: Print included vertex indices
    cout << "Included vertices in MWIS:\n";
    for (int v : included) {
        cout << v << " ";
    }
    cout << endl;

    // Specific bits to check: vertices 1, 2, 3, 4, 17, 117, 517, 997
    vector<int> query = {1, 2, 3, 4, 17, 117, 517, 997};
    cout << "Encoded MWIS presence bitstring:\n";
    for (int q : query) {
        cout << (included.count(q) ? "1" : "0");
    }
    cout << endl;

    return 0;
}
