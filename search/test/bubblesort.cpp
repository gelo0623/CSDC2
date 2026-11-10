#include <iostream>
using namespace std;

void bubbleSort(int arr[], int size, int &swaps) {
    swaps = 0;
    
    for (int i = 0; i < size - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < size - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swaps++;
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

                swapped = true;
            }
        }
        if (!swapped) {
            break;
        }
    }
}

int main() {
    int arr[100];
    int size;
    
    cin >> size;
    
    for(int i = 0; i < size; i++){
        cin >> arr[i];
    }
    
    int swaps;
    bubbleSort(arr, size, swaps);

    cout << "Sorted: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    
    cout << endl;
    cout << "Swaps: " << swaps << endl;

    return 0;
}
