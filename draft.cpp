#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

// Part 1 A
const int NUM_BANKS = 4;
string bankNames[NUM_BANKS] = {"BDO", "BPI", "Metrobank", "Security Bank"};
double localFees[NUM_BANKS] = {25, 20, 30, 15};
double intlFees[NUM_BANKS] = {150, 125, 200, 100};
double dailyLimits[NUM_BANKS] = {50000, 75000, 100000, 60000};

// Part 1 B
const int NUM_DENOMINATIONS = 2;
int denominations[NUM_DENOMINATIONS] = {500, 1000};
int billCount[NUM_DENOMINATIONS] = {500, 500}; // Current count of each 


// Part 1 c
vector<string> cardNumbers;
// Parallel vectors - keep in sync!


vector<string> encodedPINs;     
// Encoded passwords


vector<double> balances;        
// Account balances


vector<string> userBanks;        
// Which bank


vector<string> accountTypes;    
// "Local" or "International"





void addAccount(string card, string pin, double balance, string bank, string type) {
// When adding an account: 
cardNumbers.push_back(card);
encodedPINs.push_back(pin);
balances.push_back(balance);
userBanks.push_back(bank);
accountTypes.push_back(type);

}




// Part 1 D
// For each account's transaction history
vector<string> transactionTypes;    


// "Withdrawal", "Deposit", "Transfer"
vector<double> transactionAmounts;
vector<double> transactionFees;
vector<int> transactionQuantities;  


// void transaction
void logTransaction(string type, double amount, double fee) {
    bool found = false;
    for (int i = 0; i < transactionTypes.size(); i++) {
        if (transactionTypes[i] == type) {
            transactionAmounts[i] += amount;
            transactionFees[i] += fee;
            transactionQuantities[i]++;
            found = true;
            break;
        }
    }
    
    if (!found) {
        transactionTypes.push_back(type);  
        transactionAmounts.push_back(amount);
        transactionFees.push_back(fee);
        transactionQuantities.push_back(1);
        
    }
}




// Functions
int login();

void clientMenu();

void adminMenu();




// Main function
int main () {
    
    
    
    addAccount("1234567890123456", "encodedPIN: 1234", 10000, "BDO", "Local");
    logTransaction("Deposit", 5000, 0);
    
    
    
    return 0;
}





//where to do code
int login() {
    
    return 0;
}




void clientMenu () {
    
    
    
}





void adminMenu () {
    
    

}


















