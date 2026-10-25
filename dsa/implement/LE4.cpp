#include <iostream>
using namespace std;

bool sentinelSearch(int arr[], int last, int target, int &location){
    arr[last + 1] = target;
    
    
    int looker = 0;
    while(target != arr[looker]){
        looker++;
    }
    
    
    if (looker <= last){
        location = looker;
        return true;
    }
    
    else {
        location = last;
        return false;
    }
}


int main () {
    
    int arr[11] = {100, 23, 1, -3, 67, 88, 9, 10, 45, 77};
    int last = 9;
    int target;
    int location = 0;
    

    cout << "Enter the number to search: ";
    cin >> target;
    
    cout << endl;
    
    bool result = sentinelSearch(arr, last, target, location);
    
    if (result){
        cout << "Element found";
    }
    
    else {
        cout << "Element not found " << endl;
    }
    
    return 0;
}
