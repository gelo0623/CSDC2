#include <iostream>
using namespace std;

int main () {
    
    int array[10] = {4, 7, 1, 9, 3, 6, 2, 8, 5, 10};
    float sum = 0;
    float average;
    
    cout << "Array: ";
        for (int i = 0; i < 10; i++){
            cout << array[i] << " ";
        }
        
        cout << endl;
        
        
        int largest = array[0];
        for (int i = 0; i < 10; i++){
            if (array[i] >  largest){
                largest = array[i];
            }
        }
        
    
        cout << "largest: " << largest << endl;
        
        
         int smallest = array[0];
    for (int i = 0; i < 10; i++){
        if (array[i] < smallest){
            smallest = array[i];
        }
    }
        


    cout << "smallest: " << smallest << endl;

        
        
        for (int i = 0; i < 9; i++){
            
            for (int j = 0; j < 9; j++){
                
                if (array[j] < array[j + 1]){
                    
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    
                }
                
            }
        }
        
        for (int i = 0; i < 10; i++){
        sum += array[i];
        }
        cout << "Sum: " << sum << endl;
        
        average = sum / 10;
        cout  << "Average: " << sum << endl;
        
        
        for (int i = 0; i < 10; i++){
        
        if (array[i] > average){
            cout << array[i] << " Above Average" << endl;
        }
        
        else {
            cout << array[i] << " Below or Equal Average" << endl;
        }
        }
    return 0;
}

