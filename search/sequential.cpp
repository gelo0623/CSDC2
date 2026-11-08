#include <iostream>
using namespace std;

//Sequential Search / Linear Search
// 3 things to find; index(posi), value(elem), T/f
// i = 3 = T

int linearsearch (int arr[], int size, int target){
    for (int i = 0;  i < size; i++){
        if(arr[i] == target){
            return i;
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
    
    int result = linearsearch(arr, size, target);
    
    if (result != -1){
        cout << "Element found " << result <<  endl;
    }
    
    else {
        cout << "Element not found";
    }
    
    
    
    
    
    
    return 0;
}


