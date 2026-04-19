#include <iostream>
#include <string>
#include <fstream>

using namespace std;



int main () {
    string name;
    double grade;
    
    ofstream outfile("students.txt");
    
    for (int i = 0; i < 3; i++){
        cout << "Enter student name #" << i + 1 << ": ";
        cin >> name;
        
        cout << "Enter grade: ";
        cin >> grade;
        
        
        outfile << name << " " << grade << endl;
    }
    
    
    outfile.close();
    
    ifstream infile("students.txt");
    
    cout << "===== Student Records =====" << endl;
    
    while (infile >> name >> grade) {
        cout << "Name: " << name << "\tGrade: " << grade << endl;
        
    }
    
    infile.close();
    
    cout << "Records saved successfully" << endl;
    
    
    
   

    return 0;
}
