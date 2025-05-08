// two_sum_range_hash_direct.cpp
// ---------------------------------------------------------------------
// Problem: For each target t in [3, 10], check if there exist two
// distinct elements x, y in A such that x + y = t.
//
// Uses hash table lookup to efficiently check existence of (t - x).
//
// Input: "2sumSmall.txt" — list of integers
// Output: Count of valid target values
//
// Course: Stanford Algorithms Specialization - Course 2, Week 4
// ---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {
    const int num = 9;
    const int lower = 3;
    const int upper = 10;

    long long A[num];
    unordered_map<long long, bool> hashtable;

    ifstream file("2sumSmall.txt");
    long long val;
    int i = 0;

    while (file >> val && i < num) {
        A[i++] = val;
        hashtable[val] = true;
    }

    int count = 0;

    for (long long t = lower; t <= upper; ++t) {
        for (int i = 0; i < num; ++i) {
            long long complement = t - A[i];

            if (complement != A[i] && hashtable.find(complement) != hashtable.end()) {
                cout << "Found: " << A[i] << " + " << complement << " = " << t << endl;
                ++count;
                break;  // Only count t once
            }
        }
    }

    cout << "\nTotal distinct target values in [" << lower << ", " << upper << "]: " << count << endl;

    return 0;
}
