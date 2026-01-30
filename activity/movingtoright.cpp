#include <iostream>
using namespace std;

int main() {
    // Declare and initialize
    string queue[8] = {"Alice", "Bob", "Charlie", "Diana", "Eve", "", "", ""};
    int size = 5;
    string newelement = "Frank";
    int position = 2;
    

    
    
    if (size >= 8){
        cout << "Queue is full, cannot insert";
        
    }
    
    if (position < 0 || position > size){
        cout << "Invalid position";
    }
    
     
        for (int i = size - 1; i >= position; i--){
            queue[i + 1] = queue[i];
            
        }
        queue[position] = newelement;
        size = size + 1;
        
            cout << "\nOriginal Queue: Alice Bob Charlie Diana Eve";
            cout << "\nafter inserting frank at position 2: ";
            for (int i = 0; i < 8; i++){
                cout << queue[i] << " ";
            }
            
            cout << "\nNew size: " << size << endl;
        
    return 0;
}
