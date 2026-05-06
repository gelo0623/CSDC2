#include <iostream>
using namespace std;

int main() {
    int r, c;
    int sum = 0;
    
    
    cout << "Input Row: ";
    cin >> r;
    
    cout << "Input column: ";
    cin >> c;


    int arr[100][100];


    for (int i = 0; i < r; i++){
        for (int j = 0; j < c; j++)
            cin >> arr[i][j];
        
    }


    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) 
        sum += arr[i][j];
        
        
        cout << "Row " << i + 1 << ": " << sum << endl;
        
        
    }


    for (int j = 0; j < c; j++) {
        int max = arr[0][j];
        for (int i = 1; i < r; i++) 
            if (arr[i][j] > max)
                max = arr[i][j];
        cout << "Col " << j + 1 << ": " << max << endl;
        
    }

    return 0;
}
