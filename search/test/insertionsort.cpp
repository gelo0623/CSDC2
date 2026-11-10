#include <iostream>
using namespace std;

void insertionSort(int arr[], int size, int &movements) {
    movements = 0;

    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;
        

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];     
            movements++;            
            j--;
            
        }

        arr[j + 1] = key;            
    }
}



int main() {
    int arr[100];
    int size;

    cin >> size;
    
    
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
        
    }



    int movements;
    insertionSort(arr, size, movements);

    cout << "Sorted:";
    for (int i = 0; i < size; i++) {
        cout << " " << arr[i];
    }
    
    
    cout << endl;
    cout << "Movements: " << movements << endl;

    return 0;
}
