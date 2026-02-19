#include <iostream>
#include <vector>

using namespace std;

void clearScreen(){
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
}


int main () {
    
    vector<string> menuItems = {"hatdog", "burger", "fries", "chicken", "pizza"};
    vector<double> menuPrices = {39, 50, 40, 89, 99};
    
    vector<string> receiptItems;
    vector<double> receiptPrices;
    
    int choice;
    
    do {
        clearScreen();
        
        cout << "====SELF ORDERING MACHINE ====" << endl;
        cout << "= 1. View Menu               =" << endl;
        cout << "= 2. Add Item to Receipt     =" << endl;
        cout << "= 3. Remove Item from Receipt=" << endl;
        cout << "= 4. View Receipt            =" << endl;
        cout << "= 5. Exit                    =" << endl;
        cout << "==============================" << endl;
        cout << "Enter choice: ";
        cin >> choice;
        
        clearScreen();

        if(choice == 1){
            for (int i = 0; i < menuItems.size(); i++){
                cout << i << " - " << menuItems[i] << " - Php" << menuPrices[i] << endl; 
            }
            
        }
        else if(choice == 2){
            int index;
            
            for(int i = 0; i < menuItems.size(); i++){
                cout << i << " - " << menuItems[i] << " - Php" << menuPrices[i] << endl;
            }
            
            cout << "Enter item number to add: ";
            cin >> index;
            
            if(index >= 0 && index < menuItems.size()){
                receiptItems.push_back(menuItems[index]);
                receiptPrices.push_back(menuPrices[index]);
                cout << "Item added succesfully" << endl;
            }
            else {
                cout << "Invalid input" << endl;
            }
            
            cout << "Input any number to continue: ";
            cin >> choice;
            
        }
        else if(choice == 3) {
            
            if(receiptItems.empty()){
                cout << "receipt is empty";
            }
            else {
                int index;
                
                for(int i = 0; i < menuItems.size(); i++){
                cout << i << " - " << menuItems[i] << " - Php" << menuPrices[i] << endl;
                }
            
            cout << "Enter item to remove: ";
            cin >> index;
            
            
            if(index >= 0 && index < menuItems.size()){
                receiptItems.erase(receiptItems.begin() + index);
                receiptPrices.erase(receiptPrices.begin() + index);
                cout << "Item removed succesfully" << endl;
            }
            
            else {
                cout << "Invalid input" << endl;
            }
            
            }
         cout << "Input any number to continue: ";
            cin >> choice;
            
        }
        else if(choice == 4){
            if(receiptItems.empty()){
                cout << "No items orderedd yet" << endl;
            }
            
            else {
                
                double total = 0;
                
                for (int i = 0; i < receiptItems.size(); i++){
                    cout << i << " - " << menuItems[i] << " - Php" << menuPrices[i] << endl;
                    total += receiptPrices[i];
                }
                cout << "Total: Php" << total << endl;
            }
        }
        cout << "Input any number to continue: ";
            cin >> choice;
        
    }
    
    while(choice != 5);
    
    return 0;
}
