#include <iostream>
#include <string>

using namespace std;


int sum(int n){
    if (n == 0)
    return 0;
    
    return (n % 10) + sum(n / 10);
}

int f(int n) {
if (n < 10)
return n;

return f(sum(n));

}

int main () {
    int n;
    
    
    cout << "Enter numbers to flatten: ";
    cin >> n;
    
    cout << f(n);
    
    
    return 0;
}
