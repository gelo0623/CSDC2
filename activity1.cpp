#include <iostream>
using namespace std;

int main () {
    
    int array[10] = {4, 7, 1, 9, 3, 6, 2, 8, 5, 10}; // set array ofc
    float sum = 0;
    
    cout << "Array: ";
        for (int i = 0; i < 10; i++){ // i use so that it would lay out all the number inside the array
            cout << array[i] << " ";
        }
        
        cout << endl;
        
        for (int i = 0; i < 10; i++){ //this is a loop  to add all the values inside the array
        sum += array[i];
        }
        cout << "Sum: " << sum << endl;
        
        sum /= 10; // then just get the sum and divide it to the index size
        cout  << "Average: " << sum << endl;
        
        
      int largest = array[0];
      for (int i = 0; i < 10; i++){
          if (array[i] > largest){
              largest = array[i];
          }
      }
      
      int sec_largest = array[0];
      for (int i = 0; i < 10; i++){
          if (array[i] > sec_largest && array[i] < largest){
              sec_largest = array[i];
              
          }
      }
        
        cout << "Second largest: " << sec_largest << endl;
        
        
         int smallest = array[0];
    for (int i = 0; i < 10; i++){
        if (array[i] < smallest){
            smallest = array[i];
        }
    }
        
        int sec_smallest = array[0];
    for (int i = 0; i < 10; i++){
        if (array[i] < sec_smallest && array[i] > smallest){
            sec_smallest = array[i];
        }
    }

    cout << "Second smallest: " << sec_smallest << endl;

        
        // this is bubble sort
        for (int i = 0; i < 9; i++){
            // If the left value is smaller than the right value,
            // swap them so bigger values move to the front

            for (int j = 0; j < 9; j++){
                
                if (array[j] < array[j + 1]){
                    
                    int temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                    
                }
                
            }
        }
    cout << "Reversed array: ";
    for (int i = 0; i < 10; i++){
        cout << array[i] << " ";
    }


    // +2_______

    
    return 0;
}

