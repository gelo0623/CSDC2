#include <iostream>
#include <string>

using namespace std;

int main() {
    int a, b;
    
    cout << "Enter a: ";
    cin >> a;
    
    cout << "Enter b: ";
    cin >> b;
    
    int sum = a / b;
    int rem = a % b;
    rem = rem % b;
    while (b != 0);
    
    
    cout << rem;
    
    

    return 0;
}
