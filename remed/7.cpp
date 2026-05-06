#include <iostream>
#include <string>

using namespace std;


int countOccurrences(int arr[], int size, int x) {
    if (size == 0) return 0;

    if (arr[size - 1] == x)
        return 1 + countOccurrences(arr, size - 1, x);
    else
        return countOccurrences(arr, size - 1, x);
}

int main(){
    
    int n, x;
    
    cout << "Enter number of elements: ";
    cin >> n;
    
    int arr[n];
    
    cout << "Enter elements: ";
    for (int i = 0; i < n; i++){
        cin >> arr[i];
        
    }
    
    cout << "Enter what to count: ";
    cin >> x;
    
    int result = countOccurrences(arr, n, x);
    
    cout << "Occurances of " << x << " is: " << result << endl;

    
    return 0;
}
