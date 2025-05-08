// job_scheduling_ratio.cpp
// ---------------------------------------------------------------------
// Greedy algorithm to schedule jobs and minimize the weighted sum
// of completion times using the ratio strategy:
//     Ratio = weight / length
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
    vector<tuple<double, double, double>> jobs;
    int numJobs;

    ifstream file("jobs.txt");
    file >> numJobs;

    double weight, length;
    while (file >> weight >> length) {
        double ratio = weight / length;
        jobs.emplace_back(ratio, weight, length);
    }

    // Sort jobs by ratio in descending order
    sort(jobs.begin(), jobs.end(), [](const auto& a, const auto& b) {
        return get<0>(a) > get<0>(b);
    });

    long long totalLength = 0;
    long long weightedSum = 0;

    for (const auto& job : jobs) {
        totalLength += get<2>(job);                 // length
        weightedSum += totalLength * get<1>(job);   // weight * completion time
    }

    cout << "Weighted sum of completion times (ratio strategy): " << weightedSum << endl;
    // Expected output: 67311454237

    return 0;
}
