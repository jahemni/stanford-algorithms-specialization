// deterministic_selection.cpp
// ------------------------------------------------------------------
// Problem: Find the ith order statistic (ith smallest element) using
// the Deterministic Selection algorithm (Median of Medians).
//
// This is a worst-case linear time selection algorithm and is more
// predictable than QuickSelect for sensitive applications.
//
// Input: An unsorted array and an integer i (1-based)
// Output: The ith smallest element in the array
// ------------------------------------------------------------------

#include <iostream>
#include <algorithm> // for sort
#include <cmath>

using namespace std;

// Helper: Find median of an array of size n
int findMedian(int arr[], int n) {
    sort(arr, arr + n);
    return arr[n / 2];
}

// Swap two elements in an array
void swap(int arr[], int a, int b) {
    int temp = arr[b];
    arr[b] = arr[a];
    arr[a] = temp;
}

// Partition the array using a specific pivot value
int partition(int arr[], int l, int r, int pivotVal) {
    int index;
    for (index = l; index <= r; index++) {
        if (arr[index] == pivotVal) break;
    }
    swap(arr, l, index);

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

// Deterministic Selection (Median of Medians)
int dSelect(int arr[], int l, int r, int i) {
    if (l == r) return arr[l];

    int n = r - l + 1;
    int numGroups = ceil(n / 5.0);
    int medians[numGroups];

    int j;
    for (j = 0; j < n / 5; j++) {
        medians[j] = findMedian(arr + l + j * 5, 5);
    }
    if (j * 5 < n) {
        medians[j++] = findMedian(arr + l + j * 5, n % 5);
    }

    int medOfMed = (j == 1) ? medians[0] : dSelect(medians, 0, j - 1, j / 2);

    int pos = partition(arr, l, r, medOfMed);
    int k = pos - l + 1;

    if (i == k) return arr[pos];
    else if (i < k) return dSelect(arr, l, pos - 1, i);
    else return dSelect(arr, pos + 1, r, i - k);
}

int main() {
    int arr[] = {12, 3, 5, 7, 4, 19, 26, 30, 63, 38};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i = 10;  // 1-based index: 10th smallest element

    cout << "The " << i << "th smallest element is: ";
    cout << dSelect(arr, 0, n - 1, i) << endl;

    return 0;
}
