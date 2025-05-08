// two_sum_range_hash.cpp
// ----------------------------------------------------------------------
// Problem: Count the number of target values t in [lower, upper] such that
// there exists distinct x, y in the input array with x + y = t.
//
// This is a simplified version of the 2-SUM problem over a value range,
// optimized using sorting and hashing.
//
// Input: "2sumSmall.txt" — list of integers
// Output: Count of distinct target sums in [lower, upper]
// ----------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

int main() {
    const int size = 9;
    const int lower = 3;
    const int upper = 10;

    long long A[size];
    ifstream file("2sumSmall.txt");
    long long num;
    int index = 0;

    while (file >> num && index < size) {
        A[index++] = num;
    }

    sort(A, A + size);
    cout << "Input sorted." << endl;

    unordered_map<long long, bool> seenSums;
    int count = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            long long sum = A[i] + A[j];
            if (sum > upper) break;
            if (sum >= lower && A[i] != A[j] && !seenSums[sum]) {
                seenSums[sum] = true;
                ++count;
                cout << "Found valid sum: " << A[i] << " + " << A[j] << " = " << sum << endl;
            }
        }
    }

    cout << "\nTotal unique target values in range [" << lower << ", " << upper << "]: " << count << endl;
    return 0;
}
