#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* prev;
    Node* next;
    
};

typedef Node* NodePtr;


// insert a value into the list;
void insertBeginning(NodePtr& head, int newdata) {
    NodePtr newPtr = new Node;
    
    newPtr->data = newdata;
    
    
    newPtr->prev = NULL;       
    newPtr->next = head;       

    if (head != NULL)
        head->prev = newPtr;   

    head = newPtr;
}



//delete a value from the list;
void deleteValue(NodePtr& head, int value) {
    NodePtr cur = head;
    
    while (cur != NULL && cur->data != value) {
        cur = cur->next;
        
    }


    if (cur->prev != NULL){
        cur->prev->next = cur->next;  
    }
    
    else {
        head = cur->next;          
}

    if (cur->next != NULL){
        cur->next->prev = cur->prev;   

    
    }
    delete cur;
    
}



// search for a value in the list;
bool search(NodePtr head, int value) {
    NodePtr cur = head;
    
    while (cur != NULL) {
        
        if (cur->data == value) {
            return true;
        }
        
        cur = cur->next;
    }
    
    return false;
}




// Count the nodes (?)
int countNodes(NodePtr head) {
    int count = 0;
    
    NodePtr cur = head;
    
    while (cur != NULL) {
        count++;
        cur = cur->next;
        
    }
    
    return count;
}


// Display values/print
void display(NodePtr head) {
    cout << "[" << countNodes(head) << "] ";

    if (head == NULL) {
        cout << "Empty list" << endl;
        return;
    }
    

    NodePtr cur = head;
    
    while (cur != NULL) {
        cout << cur->data;
        
        
        if (cur->next != NULL)
            cout << " ";
        cur = cur->next;
    }
    
    cout << endl;
    
}

// Refresh/Reset
void refresh(NodePtr& head) {
    while (head != NULL) {
        
        NodePtr temp = head;
        head = head->next;
        delete temp;
        
    }
}



int main() {
    NodePtr head = NULL;
    char command;
    int n;


    while (cin >> command >> n) {
        if (command == 'i') {
            insertBeginning(head, n);
            display(head);
            
        }
        
        
        else if (command == 'd') {
            
            if (search(head, n)) {
                deleteValue(head, n);
                display(head);
                
            }
            
            else {
                cout << "Data not found" << endl;
                
            }
            
            
        }
        
        else if (command == 's') {
            if (search(head, n))
                cout << "Data not found" << endl;
            else
                cout << "Data not found" << endl;
        }
        
        
        else if (command == 'r') {
            refresh(head);
            display(head);
        }
    }

    return 0;
}
