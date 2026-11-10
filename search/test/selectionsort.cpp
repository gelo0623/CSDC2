#include <iostream>
using namespace std;

void selectionSort(int arr[], int size, int &comparisons, int &swaps) {
    comparisons = 0;
    swaps = 0;
    
    
    for (int i = 0; i < size - 1; i++) {
        int min = i;

        for (int j = i + 1; j < size; j++) {
            comparisons++;
            if (arr[j] < arr[min]) {
                min = j;
            }
        }
        
        if (min != i){
        int temp = arr[i];
        arr[i] = arr[min];
        arr[min] = temp;
        swaps++;
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
    
    int comparisons, swaps;
    selectionSort(arr, size, comparisons, swaps);

    
    
    
    cout << "Sorted:";
    for (int i = 0; i < size; i++){
        cout << " " << arr[i];
    }
    
    cout << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Swaps: " << swaps << endl;
    
    return 0;
}










