#include <iostream>
using namespace std;

int sentinelsearch(int arr[], int size, int target, int &comparisons){
    arr[size] = target;
    int i = 0;
    comparisons = 0;
    
    while(arr[i] != target){
        
        comparisons++;
        i++;
        
    }
    
    comparisons++;
  
    
    if (i < size){
        return i + 1;
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
    int result = sentinelsearch(arr, size, target, comparisons);
    
    if (result != -1){
        cout << "Position: " << result << endl;
    }
    
    else {
        cout << "NOT FOUND" <<endl;
    }
    
    cout << "Comparisons: " << comparisons << endl;
    return 0;
}
