// merge_sort_temp.cpp
// ---------------------------------------------
// Merge Sort using a shared auxiliary array
// ---------------------------------------------
// This version uses one shared `temp[]` array throughout the recursion.
// It's more memory-efficient and avoids multiple temporary allocations.
// Suitable for performance-critical or large-scale sorting.

#include <iostream>

using namespace std;

// Merges two sorted subarrays: arr[l..m-1] and arr[m..r]
void merge(int arr[], int temp[], int l, int m, int r) {
    int i = l, j = m, k = l;

    while (i < m && j <= r)
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

    while (i < m) temp[k++] = arr[i++];
    while (j <= r) temp[k++] = arr[j++];

    // Copy merged elements back to original array
    for (int i = l; i <= r; i++) arr[i] = temp[i];
}

// Recursive merge sort with shared temp array
void mergeSort(int arr[], int temp[], int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSort(arr, temp, l, m);
    mergeSort(arr, temp, m + 1, r);
    merge(arr, temp, l, m + 1, r);
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 3};
    int n = sizeof(arr) / sizeof(arr[0]);
    int temp[n];

    mergeSort(arr, temp, 0, n - 1);

    cout << "Sorted array:\n";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}
