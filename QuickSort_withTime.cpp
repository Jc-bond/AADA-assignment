#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>

using namespace std;
using namespace chrono;

// Partition function for quicksort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick sort function
void quick_sort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quick_sort(arr, low, pivotIndex - 1);
        quick_sort(arr, pivotIndex + 1, high);
    }
}

// Function to generate an array of specified size for best-case scenario
vector<int> generate_sorted_array(int size) {
    vector<int> arr(size);
    iota(arr.begin(), arr.end(), 1);
    return arr;
}

int main() {
    const int size = 10000;

    // Best-case scenario: Already sorted array
    vector<int> bestCase = generate_sorted_array(size);

    auto startBestCase = high_resolution_clock::now();
    quick_sort(bestCase, 0, size - 1);
    auto stopBestCase = high_resolution_clock::now();
    auto durationBestCase = duration_cast<microseconds>(stopBestCase - startBestCase);
    cout << "Best-case time: " << durationBestCase.count() << " microseconds\n";

    // Worst-case scenario: Reverse sorted array
    vector<int> worstCase = generate_sorted_array(size);
    reverse(worstCase.begin(), worstCase.end());

    auto startWorstCase = high_resolution_clock::now();
    quick_sort(worstCase, 0, size - 1);
    auto stopWorstCase = high_resolution_clock::now();
    auto durationWorstCase = duration_cast<microseconds>(stopWorstCase - startWorstCase);
    cout << "Worst-case time: " << durationWorstCase.count() << " microseconds\n";

    return 0;
}
