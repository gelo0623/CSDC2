#include <iostream>
#include <string>

using namespace std;



int main() {
    
    int a;
    int b;
    
    cout << "Enter a: ";
    cin >> a;
    
    cout << "Enter b: ";
    cin >> b;
    
    while (b != 0) {
    
    
    int temp = b;
    b = a % b;
    a = temp;
    
}
    cout << a << endl;
    
    return 0;

    
}
