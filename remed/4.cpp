#include <iostream>
using namespace std;




int main() {
    int pin;
    
    do {
        cout << "Enter pin: ";
        cin >> pin;
        
        
        if (pin != 1234) {
            cout << "Wrong PIN. Try again." << endl;
        }
        
    } while (pin != 1234);
    cout << "Access Granted" << endl;
    
    


return 0;
}
