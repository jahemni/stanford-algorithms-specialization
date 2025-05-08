// job_scheduling_difference.cpp
// ---------------------------------------------------------------------
// Greedy algorithm to schedule jobs and minimize the weighted sum
// of completion times using the difference strategy:
//     Difference = weight - length
// If differences tie, prefer job with higher weight.
//
// Input format:
// First line: number of jobs
// Remaining lines: <weight> <length> per job
//
// Output: Weighted sum of completion times
//
// Course: Stanford Algorithms Specialization - Course 3, Week 1
// ---------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

int main() {
    vector<tuple<int, int, int>> jobs;
    int numJobs;

    ifstream file("jobs.txt");
    file >> numJobs;

    int weight, length;
    while (file >> weight >> length) {
        int diff = weight - length;
        jobs.emplace_back(diff, weight, length);
    }

    // Sort jobs by (difference, weight) in descending order
    sort(jobs.begin(), jobs.end(), [](const auto& a, const auto& b) {
        if (get<0>(a) == get<0>(b))
            return get<1>(a) > get<1>(b);  // tie-breaker on weight
        return get<0>(a) > get<0>(b);
    });

    long long totalLength = 0;
    long long weightedSum = 0;

    for (const auto& job : jobs) {
        totalLength += get<2>(job);                 // length
        weightedSum += totalLength * get<1>(job);   // weight * completion time
    }

    cout << "Weighted sum of completion times (difference strategy): " << weightedSum << endl;
    // Expected output: 69119377652

    return 0;
}
