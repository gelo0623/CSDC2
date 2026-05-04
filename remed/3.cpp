#include <iostream>
using namespace std;


int main() {
    
    int n, l;
    
    cout << "Enter number: ";
    cin >> n;
    
    cout << "Enter limit: ";
    cin >> l;
    
    
    for (int i = 1; i <= n; i++){
        cout << n << " x " << i << " = " << n * i << endl;
        
    }
    

    return 0;
}
