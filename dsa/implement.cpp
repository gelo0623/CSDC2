#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

typedef Node* NodePtr;

// Insert at the beginning (newest value becomes the head)
void insertBeginning(NodePtr& head, int value) {
    NodePtr newPtr = new Node;
    newPtr->data = value;
    newPtr->prev = NULL;       // new head has nothing before it
    newPtr->next = head;       // points forward to the old head

    if (head != NULL)
        head->prev = newPtr;   // old head points back to the new node

    head = newPtr;
}

// Search for a value
bool search(NodePtr head, int value) {
    NodePtr cur = head;
    while (cur != NULL) {
        if (cur->data == value)
            return true;
        cur = cur->next;
    }
    return false;
}

// Delete the first node that holds the value
void deleteValue(NodePtr& head, int value) {
    NodePtr cur = head;
    while (cur != NULL && cur->data != value)
        cur = cur->next;

    if (cur->prev != NULL)
        cur->prev->next = cur->next;   // node before skips over cur
    else
        head = cur->next;              // cur was the first node, so head moves

    if (cur->next != NULL)
        cur->next->prev = cur->prev;   // node after skips back over cur

    delete cur;
}

// Count the nodes
int countNodes(NodePtr head) {
    int count = 0;
    NodePtr cur = head;
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

// Display: [count] values from head to the end
void display(NodePtr head) {
    cout << "[" << countNodes(head) << "] ";

    if (head == NULL) {
        cout << "EMPTY" << endl;
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

// Refresh / reset: free every node and make the list empty
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
            } else {
                cout << "VALUE NOT FOUND" << endl;
            }
        }
        else if (command == 's') {
            if (search(head, n))
                cout << "VALUE FOUND" << endl;
            else
                cout << "VALUE NOT FOUND" << endl;
        }
        else if (command == 'r') {
            refresh(head);
            display(head);
        }
    }

    return 0;
}
