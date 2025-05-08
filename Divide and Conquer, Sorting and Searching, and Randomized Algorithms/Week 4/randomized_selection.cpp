// randomized_selection.cpp
// ------------------------------------------------------------------
// Problem: Find the ith smallest element (order statistic) using
// the Randomized Selection Algorithm (QuickSelect).
//
// QuickSelect is similar to QuickSort but only recursively explores
// one side, achieving average-case O(n) time.
//
// Input: Unsorted array and integer i (1-based)
// Output: The ith smallest element
// ------------------------------------------------------------------

#include <iostream>
#include <cstdlib>   // for rand()

using namespace std;

// Swap two array elements
void swap(int arr[], int a, int b) {
    int temp = arr[b];
    arr[b] = arr[a];
    arr[a] = temp;
}

// Partition the array around the pivot index
int partition(int arr[], int l, int r, int pivotIndex) {
    swap(arr, l, pivotIndex);
    int pivot = arr[l];
    int i = l + 1;

    for (int j = l + 1; j <= r; j++) {
        if (arr[j] <= pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, l, i - 1);
    return i - 1;
}

// Randomized Selection (QuickSelect)
int rSelect(int arr[], int l, int r, int i) {
    if (l == r) return arr[l];

    int pivotIndex = l + rand() % (r - l + 1);  // Random pivot in range
    int pos = partition(arr, l, r, pivotIndex);
    int k = pos - l + 1;

    if (i == k) return arr[pos];
    else if (i < k) return rSelect(arr, l, pos - 1, i);
    else return rSelect(arr, pos + 1, r, i - k);
}

int main() {
    int arr[] = {3, 2, 10, 6, 7, 1, 9, 5, 4, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 9;  // 9th smallest (1-based)

    cout << "The " << i << "th smallest element is: ";
    cout << rSelect(arr, 0, n - 1, i) << endl;

    return 0;
}
