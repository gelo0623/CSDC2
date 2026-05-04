#include <iostream>
#include <string>

using namespace std;

int main () {
    
    int n;
    
    cout << "Input: ";
    cin >> n;
    
    if (n % 2 == 0) n++;
    int o = (n + 1) / 2;

    
    
    for(int i = 1; i <= o; i++){
        for (int j = 1; j <= o - i; j++)
            cout << " ";
    for (int k = 1; k <= 2 * i - 1; k++)
        cout << "*";
        cout << endl;
        
    }
    
    for(int i = o - 1; i >= 1; i--){
        for (int j = 1; j <= o - i; j++)
            cout << " ";
    for (int k = 1; k <= 2 * i - 1; k++)
        cout << "*";
        cout << endl;
        
    }

    
    
    
    return 0;
}
