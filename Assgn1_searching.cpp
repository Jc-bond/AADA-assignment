#include <bits/stdc++.h>
using namespace std;

void linearSearch(int *arr, int target, int size = 11)
{
    int itr = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            cout << target << " found at index " << i << endl;
            break;
        }
        else
        {
            itr++;
        }
    }
    itr == size ? cout << target << " not found in array" << endl : cout << "";
}

int int_helper = -1;

int helper(int *arr, int target, int left, int right)
{
    int mid = (left + right) / 2;
    if (arr[mid] == target)
    {
        return int_helper = mid;
    }
    else if (left == right)
        return -1;
    else
    {
        arr[mid] > target ? helper(arr, target, left, mid - 1) : helper(arr, target, mid + 1, right);
    }

    return int_helper;
}

void binarySearch(int arr[], int target, int size = 11)
{
    int_helper = -1;
    int result = helper(arr, target, 0, size - 1);
    result == -1 ? cout << target << " not present in array" << endl : cout << target << " present at index " << result << endl;
}

int main()
{
    int arr[] = {1, 4, 7, 7, 8, 9, 18, 27, 31, 56, 81};
    int target_arr[] = {1, 81, 7, 3};
    for (int i = 0; i < 4; i++)
    {
        binarySearch(arr, target_arr[i]);
    }
}