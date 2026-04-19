#include <iostream>
#include <string>

using namespace std;



int main () {
    int n;
    
    cout << "How many students?: ";
    cin >> n;
    
    string* students = new string[n];
    
    cin.ignore();
    
    for (int i = 0; i < n; i++){
        cout << "Enter student's name #" << i + 1 << ": ";
        getline(cin, students[i]);
    }
    
    cout << "\n===== Students =====" << endl;
    for (int i = 0; i < n; i++) {
        cout << students[i] << endl;
    }
    
    delete[] students;


    return 0;
}

