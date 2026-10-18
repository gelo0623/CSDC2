#include <iostream>
using namespace std;

int binarySearch (int arr[], int n, int target){
    int low = 0;
    int high = n - 1;

    while (low <= high){
        int mid = low + (high - low) / 2; // midpoint

        if(arr[mid] == target){
            return mid; //return the index if found
        }else if (target < arr[mid]){
            high = mid - 1; //search the left half, discard the upper half
        }else{
            low = mid + 1; //search the right half, discard the lower half
        }
    }
    return -1;
}

int main()
{
    int arr[] = {10, 25, 30, 45, 50}; //last index: size - 1
    int n = 5; //zero-indexing
    int target = 25;

    int result = binarySearch(arr, n, target);

    if(result != -1){
        cout << "Element found at index " << result << endl;
    }else{
        cout << "Element not found " << endl;
    }
    return 0;
}
