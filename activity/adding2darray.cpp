#include <iostream>
using namespace std;

int main() {
    // Step 1: Declare and initialize matrices
    int A[3][3] = {
        {150, 200, 180},
        {220, 190, 210},
        {170, 230, 195}
    };
    
    int B[3][3] = {
        {165, 210, 195},
        {205, 185, 200},
        {180, 240, 210}
    };
    
    int C[3][3];
    
    // Step 2: Matrix addition using nested loops
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            
            C[i][j] = A[i][j] + B[i][j];
        }
    }
    
    
    
    // Step 3: Display the result
    
    cout << "Matrix C (Total Sales from both weeks in Pesos): " << endl;
    cout <<  "       Softdrinks  Snacks  Load" << endl;
    
    for (int i = 0; i < 3; i++){
        
        if (i == 0){
            cout << "Monday     ";
        }
        else if (i == 1){
            cout << "Tuesday    ";
        }
        else {
            cout << "Wednesday  ";
        }
    
    
    for (int j = 0; j < 3; j++){
        cout << "₱" << C[i][j] << "  ";
    }
    cout << endl;

    }
    
    
    
    
    return 0;
}

