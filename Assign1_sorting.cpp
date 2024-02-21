#include <bits/stdc++.h>
using namespace std;

// {18,56,27,7,8,4,9,31,81,1}

void sorting_smallest_first(int *arr, int n = 10)
{
    int comparison = 0;
    for (int j = 0; j < n; j++)
    {
    pair<int, int> smallest = {INT_MAX, -1}; // Pair contain {element, index};
        // Find the smallest element
        for (int i = j; i < n; i++)
        {
            comparison++;
            if (arr[i] < smallest.first)
            {
                smallest.first = arr[i];
                smallest.second = i;
            }
        }

        // Swap the element 
        arr[smallest.second] = arr[j];
        arr[j] = smallest.first;
    }

    cout<<"Array after sorting ";
    for (int i=0;i<n;i++) {
        cout<<arr[i]<< " ";
    }
    cout<<endl;

    cout<<"Comparison "<<comparison<<" Iterations "<<n<<endl;
}

void bubble_Sort(int *arr, int n = 10)
{
    int comparison = 0;
    for (int j = 0; j < n; j++)
    {
    pair<int, int> max_ = {INT_MIN, -1}; // Pair contain {element, index};
        // Find the smallest element
        for (int i = 0; i < n - j; i++)
        {
            comparison++;
            if (arr[i] > max_.first)
            {
                max_.first = arr[i];
                max_.second = i;
            }
        }

        // Swap the element 
        arr[max_.second] = arr[n - j - 1];
        arr[n - j - 1] = max_.first;
    }

    cout<<"Array after sorting ";
    for (int i=0;i<n;i++) {
        cout<<arr[i]<< " ";
    }
    cout<<endl;

    cout<<"Comparison "<<comparison<<" Iterations "<<n<<endl;
}

int main()
{
    int arr[] = {18,56,27,7,8,4,9,31,81,1};

    bubble_Sort(arr);
    return 0;
}