#include <iostream>
#include <vector>
using namespace std;

vector<string> receiptItems;
vector<double> receiptPrices;
vector<int> receiptQuantities;



void displayMenu(const vector<string>& menuItems, const vector<double>& menuPrices) {
    
    cout << "============================" << endl;
    cout << "            MENU            " << endl;
    cout << "============================" << endl;
    
    for (int i = 0; i < menuItems.size(); i++) {
        cout << i << " - " << menuItems[i] << " - \u20b1" << menuPrices[i] << endl;
    }
    
}



int login(string& adminPasscode) { // here i used pass by reference so that the original variable is provided, rather than a copy of its value
    int role;
    string passcode;
    
    cout << "[1] User   [2] Admin   [3] Shutdown\n";
    cout << "Enter choice: ";
    cin >> role;


    if (role == 2) {
        cout << "Enter Admin Passcode: ";
        cin >> passcode;
        if (passcode != adminPasscode) return 0; //ayoko na sir iiyak nalang talaga ako diko na ma gets
        
    }
    return role;
    
}

void userMenu(const vector<string>& menuItems, const vector<double>& menuPrices) {
    int choice;

    while (true) {
        displayMenu(menuItems, menuPrices);

        cout << "========== USER MENU ==========" << endl;
        cout << "1. Add item" << endl;
        cout << "2. Checkout" << endl;
        cout << "3. Remove item from receipt" << endl;
        cout << "4. Exit" << endl;
        cout << "===============================" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            displayMenu(menuItems, menuPrices);

            cout << "Select item number: ";
            cin >> choice;

            int quantity;
            cout << "Enter quantity: ";
            cin >> quantity;

            bool found = false;
            for (int i = 0; i < receiptItems.size(); i++) {
                if (receiptItems[i] == menuItems[choice]) {
                    receiptQuantities[i] += quantity;
                    found = true;
                    break;
                }
            }

            if (!found) {
                receiptItems.push_back(menuItems[choice]);
                receiptPrices.push_back(menuPrices[choice]);
                receiptQuantities.push_back(quantity);
            }
        }
        else if (choice == 2) { // Checkout
            if (receiptItems.empty()) {
                cout << "Receipt is empty" << endl;
                continue;
            }

            double total = 0;
            for (int i = 0; i < receiptItems.size(); i++) {
                total += receiptPrices[i] * receiptQuantities[i];
            }

            cout << "Total: \u20b1" << total << endl;

            double payment;
            do {
                cout << "Enter payment amount: ";
                cin >> payment;
                if (payment < total)
                    cout << "Insufficient. Please enter at least " << total << endl;
            } while (payment < total);

            double change = payment - total;
            cout << "Change: \u20b1" << change << endl;

            receiptItems.clear();
            receiptPrices.clear();
            receiptQuantities.clear();
        }
        
        // REMOVE ITEM
        else if (choice == 3) { // THIS GIVE ME THE MOST PROBLEM, I NEEDED HELP SIR TwT diko to kinaya sir:(
            if (receiptItems.empty()) {
                cout << "Receipt is empty" << endl;
                continue;
            }

            for (int i = 0; i < receiptItems.size(); i++)
                cout << i << " - " << receiptItems[i] << " x " << receiptQuantities[i] << endl;

            int remo;
            cout << "Enter number to remove: ";
            cin >> remo;

            if (remo < 0 || remo >= receiptItems.size()) {
                cout << "Invalid choice!" << endl;
                continue;
            }

            if (receiptQuantities[remo] > 1)
                receiptQuantities[remo]--;
            else {
                receiptItems.erase(receiptItems.begin() + remo);
                receiptPrices.erase(receiptPrices.begin() + remo);
                receiptQuantities.erase(receiptQuantities.begin() + remo);
            }
        }
        else if (choice == 4) { // Exit user menu
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }
}


void adminMenu(vector<string>& menuItems, vector<double>& menuPrices, string& adminPasscode) { //so same hhere we need to add the adminpasscode we just implemented
    int choice;
    
    while(true){
        cout << "===== ADMIN MENU =====" << endl;
        cout << "1. View Menu" << endl;
        cout << "2. Add New Menu Item" << endl;
        cout << "3. Change Passcode" << endl;
        cout << "4. Edit Existing menu" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            displayMenu(menuItems, menuPrices);
            cout << "===========================================" << endl;
            cin.ignore(); // fixed
            cin.get(); // to enter and continue
            
        }
        
        
        else if (choice == 2) { // add menu
            string newItem;
            double newPrice;
            cin.ignore();
            
            cout << "Enter item name: ";
            getline(cin, newItem);
            
            cout << "Enter Price: ";
            cin >> newPrice;
            
            menuItems.push_back(newItem);
            menuPrices.push_back(newPrice);
        }
        
        else if (choice == 3){
            string oldPass, newPass;
            
            cout << "Enter old Passcode: ";
            cin >> oldPass;
            
            if(oldPass == adminPasscode){
                cout << "Enter new Passcode: ";
                cin >> newPass;
                
                adminPasscode = newPass;
                cout << "Passcode has been changed!" << endl;
            }
            else {
                cout << "Incorrect Passcode!" << endl;
            }
            
        }
        else if(choice == 4){ // pretty self explanatory already
            displayMenu(menuItems, menuPrices); // to display the menu and prices
            int edited;
            int edit;
            
            cout << "Enter the index to edit: ";
            cin >> edit;
            
            if (edit < 0 || edit >= menuItems.size()){
            cout << "Invalid index";
            
            }
            
            cout << "[1] Edit Name, [2] Edit Price, [3] Edit Name & Price" << endl;
            cout << "Enter choice: ";
            cin >> edited;
            cin.ignore();
            
            
            if (edited == 1){
                string newName;
                cout << "Enter new name: ";
                getline(cin, newName);
                menuItems[edit] = newName; // function that changes it so it replaces the item with newName condition by "="
            }
            
            else if (edited == 2){
                double newPrice;
                cout << "Enter new price: ";
                cin >> newPrice;
                menuPrices[edit] = newPrice;
            }
            
            else if (edited == 3){
                string newName;
                double newPrice;
                
                cout << "Enter new name: ";
                getline(cin, newName);
                 cout << "Enter new price: ";
                cin >> newPrice;
                menuItems[edit] = newName;
                menuPrices[edit] = newPrice;
            }
            
            else {
                cout << "Invalid choice" << endl;
            }
            
            cout << "Item updated!" << endl;
            
            
        }
        
        else if (choice == 5){
            break;
        
    } 
    
}
}


int main() {
    vector<string> menuItems = {"Borgir", "Pizzay", "Hatdig", "Lasagna", "FriendsPrays"};
    vector<double> menuPrices = {45, 99, 35, 67, 80};
    
    
    string adminPasscode = "0623";

    while (true) {
        int role = login(adminPasscode); // the new component has been added 
        if (role == 1) userMenu(menuItems, menuPrices);
        else if (role == 2) adminMenu(menuItems, menuPrices, adminPasscode); //nag error idk ano mali kulang pala HAHAHA
        else if (role == 3) break;
        else cout << "Access Denied.\n";
    }
    

    return 0;
}
