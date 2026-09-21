#include <iostream>
using namespace std;

struct Node { //alam mo na to
    int data;
    Node* next;
};

typedef Node* NodePtr;


// Insert a node into a sorted circular linked list
void insertNode(NodePtr& Rear, int item) { //making the block

    NodePtr New, Cur, Prev; // to track the prev, cur, and new

    // Create new node
    New = new Node; //creatig new node
    New->data = item; //storing data in item

    // Empty list
    if (Rear == NULL) { //rear is the list where the data wil be inputed from the main
        Rear = New; // sets rear as new
        New->next = New; //points the node to itself ,  rear pointing to rear
        return;
    }

    // Start at the first node
    Prev = Rear; 
    Cur = Rear->next;

    // Find the correct position
    do{
        if(item <= Cur->data)
            break;
        Prev = Cur;
        Cur = Cur->next;
    }while (Cur != Rear->next);

    // Insert the new node
    New->next = Cur;
    Prev->next = New;

    // If inserted after Rear, update Rear
    if (item > Rear->data) {
        Rear = New;
    }
}


// Delete a node from a circular linked list
void deleteNode(NodePtr& Rear, int item) {

    NodePtr Cur, Prev;

    // Empty list
    if (Rear == NULL) {
        cout << "Trying to delete empty list" << endl;
        return;
    }

    // Start at the first node
    Prev = Rear;
    Cur = Rear->next;

    // Find the node
    do {
        if (item <= Cur->data)
            break;

        Prev = Cur;
        Cur = Cur->next;

    } while (Cur != Rear->next);


    // Item was not found
    if (Cur->data != item) {
        cout << "Data Not Found" << endl;
        return;
    }


    // Only one node in the list
    if (Cur == Prev) {
        Rear = NULL;
        delete Cur;
        return;
    }


    // If deleting the Rear node
    if (Cur == Rear)
        Rear = Prev;


    // Remove Cur
    Prev->next = Cur->next;

    delete Cur;
}


// Display the circular linked list
void print(NodePtr Rear) {

    if (Rear == NULL) {
        cout << "List is empty" << endl;
        return;
    }

    NodePtr Cur = Rear->next;

    do {
        cout << Cur->data << " ";
        Cur = Cur->next;

    } while (Cur != Rear->next);

    cout << endl;
}


int main() {

    NodePtr Rear = NULL;

    // Insert values
    insertNode(Rear, 3);
    insertNode(Rear, 1);
    insertNode(Rear, 7);
    insertNode(Rear, 5);
    insertNode(Rear, 8);

    cout << "List: ";
    print(Rear);


    // Delete values
    deleteNode(Rear, 1);
    deleteNode(Rear, 3);
    deleteNode(Rear, 8);

    cout << "After deletion: ";
    print(Rear);


    // Insert again
    insertNode(Rear, 1);
    insertNode(Rear, 8);

    cout << "After insertion: ";
    print(Rear);

    return 0;
}
