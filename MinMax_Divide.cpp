#include <iostream>
#include <vector>

using namespace std;

// Structure to hold both minimum and maximum values
struct MinMax {
    int minimum;
    int maximum;
};

// Recursive function to find the minimum and maximum in an array
MinMax find_min_max(const vector<int>& arr, int low, int high) {
    MinMax result;

    // If the array contains only one element
    if (low == high) {
        result.minimum = arr[low];
        result.maximum = arr[low];
        return result;
    }

    // If the array contains two elements, compare them and return
    if (high == low + 1) {
        result.minimum = min(arr[low], arr[high]);
        result.maximum = max(arr[low], arr[high]);
        return result;
    }

    // Divide the array into two halves
    int mid = (low + high) / 2;
    MinMax left_result = find_min_max(arr, low, mid);
    MinMax right_result = find_min_max(arr, mid + 1, high);

    // Combine results from the two halves
    result.minimum = min(left_result.minimum, right_result.minimum);
    result.maximum = max(left_result.maximum, right_result.maximum);

    return result;
}

int main() {
    vector<int> arr = {3, 14, 7, 10, 4, 5, 8};

    // Call the find_min_max function
    MinMax result = find_min_max(arr, 0, arr.size() - 1);

    // Print the results
    cout << "Minimum element: " << result.minimum << endl;
    cout << "Maximum element: " << result.maximum << endl;

    return 0;
}
