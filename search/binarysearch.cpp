#include <iostream>
using namespace std;

//Sequential Search / Linear Search
// 3 things to find; index(posi), value(elem), T/f
// i = 3 = T
//sentinel search is making a new position and adding that target there
int binarysearch(int arr[], int size, int target){
    int low = 0;
    int high = size - 1;
    
    while (low <= high){
        int mid = low + (high - low) / 2;
        
        if(arr[mid] == target){
            return mid;
            
        }
        else if (target < arr[mid]){
            high = mid - 1;
            
        }
        
        else {
            low = mid + 1;
            
        }
        
    }
    return -1;
    
}

int main (){
    int arr[] =  {10, 25, 30, 45, 50};
    int size = 5;
    int target;
    
    cout << "Enter target: ";
    cin >> target;
    
    int result = binarysearch(arr, size, target);
    
    if (result != -1){
        cout << "Element found " << result <<  endl;
    }
    
    else {
        cout << "Element not found";
    }
    
    return 0;
}


