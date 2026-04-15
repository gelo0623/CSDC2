#include <iostream>
#include <string>

using namespace std;



struct Student {
    string name;
    float midterm;
    float final_exam;
    float average;
};


int main () {
    
    Student exam[5];
    
    
    cout << "===== Student Grade Report =====" << endl;
    
    for (int i = 0; i < 2; i++) {
    
    cout << "Student #" << i + 1 << endl;

cout << "Input name: ";
cin >> exam[i].name;

cout << "Input midterm score: ";
cin >> exam[i].midterm;

cout << "Input final exam score: \n";
cin >> exam[i].final_exam;


exam[i].average = exam[i].midterm + exam[i].final_exam /  2;



    }
    for (int i = 1; i <= 5; i++){
    
    cout << "==============================================" << endl;
    cout << "\nName\t\tMidterm\tFinal\tAverage\tRemark" << endl;
    cout << "----\t\t-------\t-----\t-------\t------" << endl;
    cout << "==============================================" << endl;
    
    cout << exam[i].name << "\t" << exam[i].midterm << "\t" << exam[i].final_exam << "\t" << exam[i].average
 << "\t" << (exam[i].average >= 75 ? "Passed" : "Failed") << endl;
    
    }
    
    return 0;
}
