#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<string> list;  
    string command;
    
    cout << "ADD PRODUCTS (INPUT ADD first then product)" << endl;

    while (true) {
        cin >> command;

        if (command == "DONE") {
            break;

        } else if (command == "ADD") {
            string item;
            cin >> item;
            list.push_back(item);      

        } else if (command == "REMOVE") {
            if (list.empty()) {
                cout << "List is empty." << endl;
            } else {
                list.pop_back();
            }

        } else if (command == "COUNT") {
            cout << list.size() << endl;

        } else if (command == "SHOW") {
            for (int i = 0; i < list.size(); i++) {
                cout << i + 1 << ". " << list[i] << endl;
            }
        }
    }

    cout << "Final list has " << list.size() << " item(s)." << endl;
    return 0;
}
