#include <iostream>
using namespace std;

// PART I: Initialize Function
void initQueue(int queue[5][3], int &orderCount) {
    for (int i = 0; i <= 5; i++){
        for (int j = 0; j <= 3; j++){
            queue[i][j] = 0;
            
        }
    }
    orderCount = 0;
    
}

// PART II: Insert Function
int insertOrder(int queue[5][3], int &orderCount, int orderNum) {
    for (int j = 0; j <= 2; j++){
        if (j % 2 == 0){
            for (int i = 0; i <= 4; i++){
                if (queue[i][j] == 0){
                    queue[i][j] = orderNum;
                    orderCount += 1;
                     return 1;
                }
            }
           
        }
        else {
            for (int i = 4; i <= 0; i--){
                queue[i][j] == 0;
                queue[i][j] = orderNum;
                orderCount += 1;
                return 1;
                
                }
            }
            
        }
        return 0;
        
    
    
}

// PART III: Display Function
void displayQueue(int queue[5][3], int orderCount){
    cout << "STARBUCKS ORDER QUEUE";
    cout << "       ";
    cout << endl;
    cout << "  ";
    for (int j = 0; j <= 2; j++){
        cout << "  Col" << j << " ";
        
    }
    cout << endl;
    
        for (int i = 0; i <= 4; i++){
            cout << "Row " << i << ": ";
            for (int j = 0; j <= 2; j++){
                cout << "[";
                
                if (queue[i][j] < 10){
                    cout << " " << queue[i][j];
                }
                else if (queue[i][j] < 100){
                    cout << " " << queue[i][j];
                }
                
                else {
                    
                    cout << queue[i][j];
                
                   
                }
               cout << "] ";
                
            }
            cout << endl;
        
    }
    
    cout << "Total orders: " << orderCount;
}

// PART IV: Search Function
int searchOrder(int queue[5][3], int orderNum) {
    for (int i = 0; i <= 4; i++){
        for (int j = 0; j <= 2; j++){
            if (queue[i][j] == orderNum){
                return 1;
            }
            
        }
    }
    
    return 0;
}


// BONUS: Count Column Function
int countColumn(int queue[5][3], int colNum) {
    
    int counter = 0;
    
    for (int i = 0; i <= 4; i++){
        if (queue[i][colNum] != 0){
            counter += 1;
            
        }
    }
    return counter;
    
    
}

// PART V: Main Function
int main() {
    
    int queue[5][3];
    int orderCount = 0;
    
    initQueue(queue, orderCount);
    int orders[8] = {101, 102, 103, 104, 105, 106, 107, 108};
    
    
    for (int i = 0; i <= 7; i++){
        insertOrder(queue, orderCount, orders[i]);
        
    }
    
    displayQueue(queue, orderCount);
        
        
    cout << endl;
    

int result = searchOrder(queue, 105);

if (result == 1){
    cout << "Order 105 found in queue!";
}

else {
    
    cout << "Order 105 not found.";

}
cout << endl;

int result2 = searchOrder(queue, 999);
if (result2 == 1){
    cout << "Order 999 found in queue!";

    
}
else {
    cout << "Order 999 not found.";
}
    
    cout << endl;
int col0Count = countColumn(queue, 0);
cout << "Orders in Column 0: " << col0Count << endl;

int col1Count = countColumn(queue, 1);
cout << "Orders in Column 1: " << col1Count << endl;

    
    
    return 0;
}
