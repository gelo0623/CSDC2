#include <iostream>
using namespace std;

int main() {
    int num, exponent, result = 1; 
    
    cout << "Enter the base: ";
    cin >> num;
    
    cout << "Enter exponent: ";
    cin >> exponent;
    
    for (int i = 1; i <= exponent; i++){ 
        result *= num;
    }
    cout << num << "^" << exponent << " = " << result << endl;
    
    return 0;
}
