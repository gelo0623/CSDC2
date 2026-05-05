#include <iostream>
#include <string>

using namespace std;

string reverseString(string s) {
    
    if (s.length() <= 1) return s;
    return reverseString(s.substr(1)) + s[0];
}

int main () {
    string s;
    cout << "Enter word: ";
    cin >> s;
    
    cout << reverseString(s) << endl;
    
  
    return 0;
}
