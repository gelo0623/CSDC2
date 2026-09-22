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
    Prev = Rear; // makes the rear the previous node // so like the cur to prev
    Cur = Rear->next; // the next of the previous makes it the current

    // Find the correct position
    do{
        if(item <= Cur->data) // keeps looping until the data matches the current data position
            break;

        // runs if its false to the statement
        Prev = Cur; // makes the current as the previous node
        Cur = Cur->next; // mpoints the cur to the next node and make it as the cur / moves to one more node
    }while (Cur != Rear->next); // did the cur gets back to line 1/ after traversing to the whole list back to the start

    // Insert the new node
    New->next = Cur; // new->next holds the copy of the cur data node it has -> so that the cur moves to the next so 5 becoms 7
    Prev->next = New; // prev was 3 and now points to next which is 5

    // If inserted after Rear, update Rear
    if (item > Rear->data) { //rear holds theh largest so checks is the value bigger than the current largest
        Rear = New; // and if yes it moves the rear to the new largest
    }
}


// Delete a node from a circular linked list
void deleteNode(NodePtr& Rear, int item) {

    NodePtr Cur, Prev;

    // Empty list
    if (Rear == NULL) { //if the rear is pointinf to nothing
        cout << "Trying to delete empty list" << endl;
        return;
    }

    // Start at the first node
    Prev = Rear; // creating node // makes the current rear as the previousnode
    Cur = Rear->next; // the next of the  rear makes it as the current node

    // Find the node
    do {
        if (item <= Cur->data) //keeps looping until it matches the data current position
            break;

        // runs if false statement
        Prev = Cur; // makes the curent node as the previous
        Cur = Cur->next; //current node is pointing to the next and makes that the currrent

    } while (Cur != Rear->next); // if cur does not yet stilll matchhes the rear position it keeps looping


    // Item was not found
    if (Cur->data != item) { //if the current data is not on the item
        cout << "Data Not Found" << endl;
        return;
    }


    // Only one node in the list
    if (Cur == Prev) { // if theres only 1 node, set rear to NULL and delete the node
        Rear = NULL;
        delete Cur;
        return;
    }


    // If deleting the Rear node
    if (Cur == Rear) //makes the previous node the rear when deleting
        Rear = Prev;


    // Remove Cur
    Prev->next = Cur->next; //unlinks the memory

    delete Cur; //delete
}


// Display the circular linked list
void print(NodePtr Rear) {

    if (Rear == NULL) { //if list  is empyt
        cout << "List is empty" << endl;
        return;
    }

    NodePtr Cur = Rear->next; // makes the next of the rear the current node

    do {
        cout << Cur->data << " "; //rint the current data
        Cur = Cur->next; //moves the current node

    } while (Cur != Rear->next); //keeps repeating until reaches the position original //keeps printing 

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
