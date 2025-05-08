// count_inversions.cpp
// -------------------------------------------------
// Problem: Count the number of inversions in an array.
// -------------------------------------------------
// An inversion is a pair (i, j) such that i < j and arr[i] > arr[j].
// This implementation uses a modified Merge Sort to count inversions
// efficiently in O(n log n) time.
//
// Input: A list of integers from "IntegerArray.txt"
// Output: Total number of inversions in the array

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Merge two sorted subarrays and count cross-inversions
unsigned int merge(int arr[], int temp[], int left, int mid, int right) {
    unsigned int inversions = 0;
    int i = left;     // pointer for left subarray
    int j = mid;      // pointer for right subarray
    int k = left;     // pointer for merged array

    while (i < mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += mid - i;  // all remaining elements in left > arr[j]
        }
    }

    // Copy remaining elements from both subarrays
    while (i < mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];

    // Copy sorted data back to original array
    for (int i = left; i <= right; i++) {
        arr[i] = temp[i];
    }

    return inversions;
}

// Recursive function to count inversions via divide-and-conquer
unsigned int countInversions(int arr[], int temp[], int left, int right) {
    if (left >= right) return 0;

    int mid = (left + right) / 2;
    unsigned int inversions = 0;

    inversions += countInversions(arr, temp, left, mid);
    inversions += countInversions(arr, temp, mid + 1, right);
    inversions += merge(arr, temp, left, mid + 1, right);

    return inversions;
}

int main() {
    const int arr_size = 100000;
    int arr[arr_size];
    int temp[arr_size];

    ifstream file("IntegerArray.txt");
    string line;
    int i = 0;

    while (getline(file, line) && i < arr_size) {
        arr[i++] = stoi(line);
    }

    file.close();

    unsigned int total_inversions = countInversions(arr, temp, 0, arr_size - 1);
    cout << "Total Inversions: " << total_inversions << endl;

    return 0;
}
