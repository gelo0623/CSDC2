#include <iostream>
using namespace std;

//Sequential Search / Linear Search
// 3 things to find; index(posi), value(elem), T/f
// i = 3 = T

//sentinel search is making a new position and adding that target there


int probabilitysearch(int arr[], int size, int target){
    for (int i = 0;  i < size; i++){
        if(arr[i] == target){
            if (i > 0) {
                int temp = arr[i - 1];
                arr[i - 1] = arr[i];
                arr[i] = temp;
                return i - 1;
            }
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
    
    int result = probabilitysearch(arr, size, target);
    
    if (result != -1){
        cout << "Element found " << result <<  endl;
    }
    
    else {
        cout << "Element not found";
    }
    
    
    
    
    
    
    return 0;
}


