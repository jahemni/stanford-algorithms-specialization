// median_maintenance.cpp
// ------------------------------------------------------------------
// Problem: Maintain the median of a stream of integers using two heaps.
// 
// Approach: Use a Max Heap for the lower half, and a Min Heap for the
// upper half of the input stream. Keep heaps balanced such that the
// max heap (lower half) always contains the current median or one more
// than the min heap.
//
// At each step, output the current median and compute the running sum.
// 
// Input: "Median.txt" — one integer per line
// Output: Sum of medians modulo 10000
//
// Course: Stanford Algorithms Specialization - Course 2, Week 3
// ------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

int main() {
    // Max Heap for the lower half
    priority_queue<int> maxHeap;

    // Min Heap for the upper half
    priority_queue<int, vector<int>, greater<int>> minHeap;

    // Initialize with dummy values to simplify comparison
    maxHeap.push(0);
    minHeap.push(99999);

    int medianSum = 0;

    ifstream file("Median.txt");
    string line;

    while (getline(file, line)) {
        int num = stoi(line);

        // Insert the number in the appropriate heap
        if (maxHeap.size() > minHeap.size()) {
            if (num < maxHeap.top()) {
                minHeap.push(maxHeap.top());
                maxHeap.pop();
                maxHeap.push(num);
            } else {
                minHeap.push(num);
            }
            medianSum = (medianSum + maxHeap.top()) % 10000;
        } 
        else if (minHeap.size() > maxHeap.size()) {
            if (num > minHeap.top()) {
                maxHeap.push(minHeap.top());
                minHeap.pop();
                minHeap.push(num);
            } else {
                maxHeap.push(num);
            }
            medianSum = (medianSum + maxHeap.top()) % 10000;
        } 
        else { // Heaps are equal size
            if (num > minHeap.top()) {
                minHeap.push(num);
                medianSum = (medianSum + minHeap.top()) % 10000;
            } else {
                maxHeap.push(num);
                medianSum = (medianSum + maxHeap.top()) % 10000;
            }
        }
    }

    cout << "Sum of medians modulo 10000: " << medianSum << endl;
    return 0;
}
