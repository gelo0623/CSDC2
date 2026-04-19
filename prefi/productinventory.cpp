#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void clearScreen(){
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

struct Product {
  string name;
  int quantity;
  float price;
    
};


int main () {
    
    Product max[5];
    int n;
    float total;
    
    do {
    cout << "===== PRODUCT INVENTORY =====" << endl;
    
    cout << "How many products to enter (max 5): ";
    cin >> n;
    clearScreen();
    
    if (n > 5) {
        cout << "Maximum is 5 products only!\n";
        cout << "\n";
        
    }
    } while (n > 5);
    
    
    
    
    for (int i = 0; i < n; i++){
        cout << "Product #" << i + 1 << endl;
        
        cout << "Enter product name: ";
        cin >> max[i].name;
        
        cout << "Enter quantity: ";
        cin >> max[i].quantity;
        
        cout << "Enter price: ";
        cin >> max[i].price;
    }
    
    cout << "================ Product List ===============" << endl;
    cout << "Name\t\tQuantity\tPrice\tTotal Value" << endl;
    cout << "---------------------------------------------" << endl;
    
     for (int i = 0; i < n; i++) {
        total = max[i].quantity * max[i].price;
         
        cout << max[i].name << "\t\t" << max[i].quantity << "\t" << max[i].price 
        << "\t" << total << endl;
    }

    int mostExpensive = 0;
    
    for (int i = 0; i < n; i++){
        if(max[i].price > max[mostExpensive].price) {
            mostExpensive = i;
        }
    }
    cout << "\n";
    
    cout << "===== MOST EXPENSIVE ITEM =====" << endl;
    cout << "Name: " << max[mostExpensive].name << endl;
    cout << "Price: " << max[mostExpensive].price << endl;

    
    
    return 0;
}
