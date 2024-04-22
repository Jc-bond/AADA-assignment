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

void bubbleSort(int arr[], int n)
{

    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        if (swapped == false)
            break;
    }

    // Print the sorted array 
    for (int i = 0; i < n; i++)
        cout << " " << arr[i];
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
 
        // Move elements of arr[0..i-1],
        // that are greater than key, 
        // to one position ahead of their
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    // Print the sorted array 
    for (int i = 0; i < n; i++)
        cout << " " << arr[i];
}

void mergeArrays(int arr1[], int arr2[], int n1,
                            int n2)
{
    int sortedArray[n1+n2] = {0};
    int i = 0, j = 0, k = 0;
 
    // Traverse both array
    while (i<n1 && j <n2)
    {
        if (arr1[i] < arr2[j])
            sortedArray[k++] = arr1[i++];
        else
            sortedArray[k++] = arr2[j++];
    }
 
    // Store remaining elements of first array
    while (i < n1)
        sortedArray[k++] = arr1[i++];
 
    // Store remaining elements of second array
    while (j < n2)
        sortedArray[k++] = arr2[j++];

    for(int i=0;i<n1+n2;i++) {
        cout<<" "<<sortedArray[i];
    }
    cout<<endl;
}

// Merge Sort

void merge(int array[], int const left, int const mid,
           int const right)
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;
 
    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];
 
    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;
 
    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne
           && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne]
            <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray]
                = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else {
            array[indexOfMergedArray]
                = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]
            = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
 
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray]
            = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}
 
void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end)
        return;
 
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

// quick sort

int partition(int arr[],int low,int high)
{
  //choose the pivot
   
  int pivot=arr[high];
  //Index of smaller element and Indicate
  //the right position of pivot found so far
  int i=(low-1);
   
  for(int j=low;j<=high;j++)
  {
    //If current element is smaller than the pivot
    if(arr[j]<pivot)
    {
      //Increment index of smaller element
      i++;
      swap(arr[i],arr[j]);
    }
  }
  swap(arr[i+1],arr[high]);
  return (i+1);
}
 
// The Quicksort function Implement
            
void quickSort(int arr[],int low,int high)
{
  // when low is less than high
  if(low<high)
  {
    // pi is the partition return index of pivot
     
    int pi=partition(arr,low,high);
     
    //Recursion Call
    //smaller element than pivot goes left and
    //higher element goes right
    quickSort(arr,low,pi-1);
    quickSort(arr,pi+1,high);
  }
}


int main()
{
    int arr[] = {18,56,27,7,8,4,9,31,81,1};

    bubbleSort(arr,10);
    return 0;
}