#include <iostream>

using namespace std;

int main () {
    int n = 3;
       for (int i = 0; i <= n; i++){
           for (int j = 0; j <= n; j++){
           cout << "*    ";
       }
       cout << endl;
       }
      
    for (int i = 0; i < 6; i++){
        cout << "*  ";
    }
    
    for (int j = 0; j < 7; j++){
        for (int i = 0; i < 1; i++){
        cout << "        *";
    }
    cout << endl;
    }
    
    
    return 0;
}
