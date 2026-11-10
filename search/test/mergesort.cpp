#include <iostream>
using namespace std;

void merge(int arr[], int left, int mid, int right, int &comparisons, int &movement){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++){
        L[i] = arr[left + i];
    }

    for (int j = 0; j < n2; j++){
        R[j] = arr[mid + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = left;

    while (i < n1 && j < n2){
        comparisons++;
        if (L[i] <= R[j]){
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
        movement++;
    }

    while (i < n1){
        arr[k] = L[i];
        i++;
        k++;
        movement++;
    }

    while (j < n2){
        arr[k] = R[j];
        j++;
        k++;
        movement++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right, int &comparisons, int &movement){
    if (left < right){
       int mid = left + (right - left + 1) / 2 - 1;

        mergeSort(arr, left, mid, comparisons, movement);
        mergeSort(arr, mid + 1, right, comparisons, movement);

        merge(arr, left, mid, right, comparisons, movement);
    }
}

int main()
{
    int arr[100];
    int n;
    
    cin >> n;

    for (int i = 0; i < n; i++){
        cin >> arr[i];
    }
    
    
    int comparisons = 0;
    int movement = 0;
    mergeSort(arr, 0, n - 1, comparisons, movement);
    
    cout << "Sorted: ";
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    
    cout << endl;
    cout << "Comparisons: " << comparisons << endl;
    cout << "Movements: " << movement << endl;

    return 0;
}
