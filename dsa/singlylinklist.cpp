#include <iostream>
using namespace std;

//making the pointer
struct Node {
    int data; //wheer tp store the data
    Node* next; //the pointer to next
};

typedef Node* NodePtr; //allias another way to call

// Add at the beginning
void addHead(NodePtr& head, int newdata) { //since add head ofc you need head and  newdata values to use and use & so its universalthat pass the actual value not just a copy
    NodePtr newPtr = new Node; //create a new node and store it to "Node" while new is a built in funtion of C++ that grabs a chunk of memory

    newPtr->data = newdata; //where you store your data
    newPtr->next = head; // points to the next node // from 1sthead to 2nd head

    head = newPtr; //makes what or where it was pointed the head.
}

// Add at the end
void addEnd(NodePtr& head, int newdata) {
    NodePtr newPtr = new Node; // creating a new node and allocating it

    newPtr->data = newdata; //the same adding data
    newPtr->next = NULL; //pointing the next to NULL so it does not point to anymore next

    if (head == NULL) { //and if it points to null
        head = newPtr; //makes the current the head
    }
    else {
        NodePtr last = head; //last is a variable and its making it equal to head, so making it head/ givesit a copy so last is also head

        while (last->next != NULL) { // while last to next pointer is not pointing to none
            last = last->next; // last keeps moving until it reaches null
        }

        last->next = newPtr; //when the loop ends last->next was holding the null, now it allocated it to newPtr
    }
}

// Delete first node
void deleteHead(NodePtr& head) {
    if (head != NULL) { //if head is empty, do nothing
        NodePtr p = head; // save current head in p

        head = head->next; // move head to next node

        delete p; //delete old head after moving the head
    }
}

// Display
void displayList(NodePtr head) {
    NodePtr p = head; //making p the head

    while (p != NULL) { //if p doesnt points to null
        cout << p->data << " "; // prinnt p and its data that its currently on and then moves 
        p = p->next; // p moves to the next node
    } 

    cout << endl; // after p points to null, it stops
}

int main() {

    NodePtr head = NULL;

    // Add nodes
    addHead(head, 20);
    addHead(head, 13);
    addEnd(head, 40);

    cout << "List: ";
    displayList(head);

    // Delete first node
    deleteHead(head);

    cout << "After deleting head: ";
    displayList(head);

    // Add another node
    addHead(head, 50);

    cout << "After adding 50 at head: ";
    displayList(head);

    return 0;
}
