#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

};

typedef Node* NodePtr; //Node* and nodeptr is the same thing

// Insertion
// Insert a node into a started circular linked list
void insertNode(NodePtr& Rear, int item) {//passbyref and variables

    NodePtr New, Cur, Prev;

    //create a new node
    New = new Node;
    New->data = item; // storing the value to the item var
    

    //empty list
    if (Rear == NULL){
        Rear = New;
        New->next = New;
        return;
    }
    //start at the first node
    Prev = Rear;
    Cur = Rear->next;

    //Find the correct position
    do{
        if (item <= Cur->data)
        break;
        Prev = Cur;
        Cur = Cur->next;
    } while(Cur != Rear->next);

    //Insert the new node
    New->next = Cur;
    Prev->next = New;

    //if inserted after Rear, Update Rear
    if (item > Rear->data){
        Rear = New;
    }
}


//Delete a node from a circular linked list
void deleteNode(NodePtr& Rear, int item) {
    
    NodePtr Cur, Prev;

    // empty list
    if(Rear == NULL){
        cout << "Trying to delete empty list" << endl;
        return;
    }
    
    // start at the first Node
    Prev = Rear;
    Cur = Rear->next;
    
    //Find the Node
    do {
        if (item <= Cur->data)
        break;
        
        Prev = Cur;
        Cur = Cur->next;
        
    }
    while (Cur != Rear->next);
    
    //item not found
    if (Cur->data != item){
        cout << "Data not found" << endl;
        return;
    }
    
    
    //only one node in the list
    if (Cur == Prev) {
        Rear = NULL;
        delete Cur;
        return;
    }
    
    //if deleting the rear Node
    if (Cur == Rear)
    Rear = Prev;
    
    // remove current
    Prev->next = Cur->next;
    
    delete Cur;
    
}

void print(NodePtr Rear){
    
    if (Rear == NULL){
        cout << "List is empty" << endl;
        return;
    }
    
    NodePtr Cur = Rear->next;
    
    do{
        cout << Cur->data << " ";
        Cur = Cur->next;
    }
    while (Cur != Rear->next);
    
    cout << endl;
    
    
}


int main () {
    
    NodePtr Rear = NULL;
    
    //Insert values
    insertNode(Rear, 3);
    insertNode(Rear, 1);
    insertNode(Rear, 7);
    insertNode(Rear, 5);
    insertNode(Rear, 8);
    
    cout << "List: ";
    print(Rear);
    
    
    
    //Delete values
    deleteNode(Rear, 1);
    deleteNode(Rear, 3);
    deleteNode(Rear, 8);
    
    cout << "After deletion: ";
    print(Rear);
    
    
    
    //Insert again
    insertNode(Rear, 1);
    insertNode(Rear, 8);
    
    
    cout << "After insertion: ";
    print(Rear);
    
    
    
    
    
    return 0;
}



























