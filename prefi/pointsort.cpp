#include <iostream>
#include <string>

using namespace std;


void bubbleSort(int* arr, int size) {
    for (int i = 0; i < size - 1; i++) { // this is the outer loop and will run for 4 times

        // Inner loop runs 4 times and compares each one
        for (int j = 0; j < size - 1; j++) {

      
            if (*(arr + j) > *(arr + j + 1)) { // if the current number is greater to the next, this swaps them

                int temp = *(arr + j);
                *(arr + j) = *(arr + j + 1);
                *(arr + j + 1) = temp;
            }
        }
    }
    
    
    
}

int main () {
    int arr[5];
    
    cout << "Input 5 integers:";
    for (int i = 0; i < 5; i++){
        cin >> arr[i];
    };
    
    cout << "Before: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
        
    };
    
    
    
    
    
    bubbleSort(arr, 5);
    
    cout << "\nAfter: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
        
    };


    return 0;
}

