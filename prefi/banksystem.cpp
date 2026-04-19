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

class BankAccount {
    
private:
  string accountHolder;
  double balance;
    
    
public:
BankAccount(string name, double initialDeposit){
    accountHolder = name;
    balance = initialDeposit;
    
}

void deposit (double amount){
    if (amount > 0) {
        balance += amount;
            cout << "Deposit successful" << endl;
        } else {
            cout << "Invalid amount" << endl;
        }
    
}

void withdraw (double amount){
     if (amount > balance) {
            cout << "Insufficient funds" <<endl;
        } else if (amount <= 0) {
            cout << "Invalid amount" << endl;
        } else {
            balance -= amount;
            cout << "Withdrawal successful" << endl;
        }
    
} 

void displayBalance(){
    
    cout << "Balance: " << balance << endl;
}

    
};





int main () { 
    string name;
    double initialDeposit;
    
    
    cout << "========== Bank Account System ==========" << endl;
    cout << "Enter Account Holder Name: ";
    getline(cin, name);
    
    cout << "Enter Deposit: ";
    cin >> initialDeposit;
    
    
    BankAccount account(name, initialDeposit);
    
    int choice;
    double amount;
    
    do {
    cout << "===== BANK MENU SYSTEM =====" << endl;
    cout << "[1] Deposit" << endl;
    cout << "[2] Withdraw" << endl;
    cout << "[3] Check Balance" << endl;
    cout << "[4] Exit" << endl;
    cout << "Enter choice: ";
    cin >> choice;
    
    if (choice == 1){
        cout << "Enter amount to deposit: ";
        cin >> amount;
        account.deposit(amount);
        
    }
    
    else if (choice == 2){
        cout << "Enter amouut to Withdraw: ";
        cin >> amount;
        account.withdraw(amount);
    }
    
    else if (choice == 3){
        account.displayBalance();
    }
    
    else if (choice == 4){
        cout << "Gooodbyeeee....";
        break;
        
    }
    
    else {
        cout << "Invalid choice";
        break;
    }
    
    
    } while (choice != 4);
    
    
    
    
    return 0;
}

