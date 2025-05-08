// quicksort_median_demo.cpp
// ------------------------------------------------------
// Demonstration of QuickSort using median-of-three pivot
// strategy on a small, hardcoded array.
//
// This version uses the Lomuto partition scheme and picks
// the pivot as the median of the first, middle, and last
// elements for better performance on partially sorted arrays.
// ------------------------------------------------------

#include <iostream>
#include <algorithm>  // for std::min, std::max

using namespace std;

// Swap helper
void swap(int arr[], int a, int b) {
    int temp = arr[b];
    arr[b] = arr[a];
    arr[a] = temp;
}

// Returns the index of the median of arr[l], arr[mid], arr[r]
int findMedianIndex(int arr[], int l, int r) {
    int n = r - l + 1;
    int mid = l + n / 2 - (n % 2 == 0 ? 1 : 0);

    int a = arr[l], b = arr[mid], c = arr[r];
    int maxi = max({a, b, c});
    int mini = min({a, b, c});

    if (a != maxi && a != mini) return l;
    else if (b != maxi && b != mini) return mid;
    else return r;
}

// Partition with the given pivot index
int partition(int arr[], int l, int r, int pivotIndex) {
    swap(arr, l, pivotIndex);
    int pivot = arr[l];
    int i = l + 1;

    for (int j = l + 1; j <= r; j++) {
        if (arr[j] < pivot) {
            swap(arr, i, j);
            i++;
        }
    }
    swap(arr, l, i - 1);
    return i - 1;
}

// QuickSort using median-of-three pivot strategy
void quickSort(int arr[], int l, int r) {
    if (l >= r) return;

    int pivotIndex = findMedianIndex(arr, l, r);
    int pivotFinal = partition(arr, l, r, pivotIndex);

    quickSort(arr, l, pivotFinal - 1);
    quickSort(arr, pivotFinal + 1, r);
}

int main() {
    int arr[] = { 3, 2, 10, 6, 7, 1, 9, 5, 4, 8 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    quickSort(arr, 0, arr_size - 1);

    cout << "Sorted array:\n";
    for (int i = 0; i < arr_size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}
