#include <iostream>
using namespace std;

int binarysearch(int arr[], int size, int target, int &comparisons){
    int low = 0;
    int high = size - 1;
    comparisons = 0;
    
    while (low <= high){
        int mid = low + (high - low) / 2;
        comparisons++;
        
        if(arr[mid] == target){
            return mid + 1;
            
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
    int arr[100];
    int size;
    int target;
    

    cin >> size;
    
    
    for (int i = 0; i < size; i++){
        cin >> arr[i];
    }
    
    
    cin >> target;
    
    int comparisons;
    int result = binarysearch(arr, size, target, comparisons);
    
    if (result != -1){
        cout << "Position: " << result << endl;
    }
    
    else {
        cout << "NOT FOUND" <<endl;
    }
    
    cout << "Comparisons: " << comparisons << endl;
    return 0;
}
