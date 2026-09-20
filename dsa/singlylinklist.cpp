#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

typedef Node* NodePtr;

// Add at the beginning
void addHead(NodePtr& head, int newdata) {
    NodePtr newPtr = new Node;

    newPtr->data = newdata;
    newPtr->next = head;

    head = newPtr;
}

// Add at the end
void addEnd(NodePtr& head, int newdata) {
    NodePtr newPtr = new Node;

    newPtr->data = newdata;
    newPtr->next = NULL;

    if (head == NULL) {
        head = newPtr;
    }
    else {
        NodePtr last = head;

        while (last->next != NULL) {
            last = last->next;
        }

        last->next = newPtr;
    }
}

// Delete first node
void deleteHead(NodePtr& head) {
    if (head != NULL) {
        NodePtr p = head;

        head = head->next;

        delete p;
    }
}

// Display
void displayList(NodePtr head) {
    NodePtr p = head;

    while (p != NULL) {
        cout << p->data << " ";
        p = p->next;
    }

    cout << endl;
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
