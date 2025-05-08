// quicksort_comparisons.cpp
// ---------------------------------------------------------
// Problem: Implement QuickSort with median-of-three pivot strategy
// and count the number of comparisons made during sorting.
//
// This is based on the Week 3 assignment of Stanford's
// Algorithms Specialization (Coursera).
//
// The code reads 10,000 integers from "QuickSort.txt", sorts them
// using QuickSort, and reports the total number of comparisons.
// ---------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>  // for std::max and std::min

using namespace std;

// Swap helper
void swap(int arr[], int a, int b) {
    int temp = arr[b];
    arr[b] = arr[a];
    arr[a] = temp;
}

// Returns index of median-of-three pivot among arr[l], arr[mid], arr[r]
int findMedianIndex(int arr[], int l, int r) {
    int mid = l + (r - l) / 2;
    int a = arr[l], b = arr[mid], c = arr[r];

    if ((a > b) != (a > c)) return l;
    else if ((b > a) != (b > c)) return mid;
    else return r;
}

// Partition the array using Lomuto partition scheme
int partition(int arr[], int l, int r, int pivotIndex) {
    swap(arr, l, pivotIndex);  // move pivot to the beginning
    int pivot = arr[l];
    int i = l + 1;

    for (int j = l + 1; j <= r; j++) {
        if (arr[j] < pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, l, i - 1);  // place pivot in correct position
    return i - 1;         // return pivot final index
}

// QuickSort that returns number of comparisons
int quickSort(int arr[], int l, int r) {
    if (l >= r) return 0;

    int pivotIndex = findMedianIndex(arr, l, r);  // Use median-of-three
    int pivotFinal = partition(arr, l, r, pivotIndex);

    int leftComparisons = quickSort(arr, l, pivotFinal - 1);
    int rightComparisons = quickSort(arr, pivotFinal + 1, r);

    return (r - l) + leftComparisons + rightComparisons;
}

int main() {
    const int arr_size = 10000;
    int arr[arr_size];
    ifstream file("QuickSort.txt");
    string line;
    int i = 0;

    // Read integers from file
    while (getline(file, line) && i < arr_size) {
        arr[i++] = stoi(line);
    }
    file.close();

    // Perform QuickSort and count comparisons
    int totalComparisons = quickSort(arr, 0, arr_size - 1);
    cout << "Total comparisons using median-of-three pivot: " << totalComparisons << endl;

    return 0;
}
