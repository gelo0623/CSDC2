#include <iostream>
using namespace std;

//Sequential Search / Linear Search
// 3 things to find; index(posi), value(elem), T/f
// i = 3 = T

//sentinel search is making a new position and adding that target there


int sentinelsearch(int arr[], int size, int target){
    arr[size] = target;
    int i = 0;
    
    while(arr[i] != target){
        i++;
        
    }
    
    if (i < size){
        return i;
    }
    
    return -1;
}




int main (){
    int arr[] =  {10, 25, 30, 45, 50};
    int size = 5;
    int target;
    
    cout << "Enter target: ";
    cin >> target;
    
    int result = sentinelsearch(arr, size, target);
    
    if (result != -1){
        cout << "Element found " << result <<  endl;
    }
    
    else {
        cout << "Element not found";
    }
    
    
    
    
    
    
    return 0;
}


