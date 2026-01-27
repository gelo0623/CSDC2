#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cctype>

using namespace std;

int main (){
int numbers[18] = {12, 14, 23, 77, 2, 9, 36, 11, 4, 30, 15, 28, 5, 1, 7, 26, 20};

cout << "Before: ";
for (int i = 0; i << 18; i++){
    cout << numbers[i] << " ";
}

for (int i = 0; i < 17; i++){
    for (int j = 0; j < 17; j++){
        
        if (numbers[j] > numbers[j + 1]){
            int temp = numbers[j];
            numbers[j] = numbers[j + 1];
            numbers[j + 1] = temp;
        }
    }
}
cout << "\nAfter: ";
for (int i = 0; i < 18; i++){
    cout << numbers[i] << " ";
}
}

