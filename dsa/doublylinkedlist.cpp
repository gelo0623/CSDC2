#include <iostream>
using namespace std;

struct Node {
    int data; // store data
    Node* next; // stores address
    Node* prev; //both directions
};

typedef Node* NodePtr;

//create an empty doubly linkedlist
void createHead(NodePtr& Head){
    Head = new Node;
    Head->next = Head; // points to itself in both directions //necessary even if we have an empty list
    Head->prev = Head;
}

void insertNode(NodePtr Cur, int item){
    NodePtr New = new Node;
    New->data = item;
    
    //connection of new to cur
    New->next = Cur; // cur = 2= ->new
    New->prev = Cur->prev; //points backward
    
    //connection of cur to New
    Cur->prev = New;
    (New->prev)->next = New;
    
}

void deleteNode(NodePtr Cur){
    (Cur->prev)->next = Cur->next; //previous to next
    (Cur->next)->prev = Cur->next; //next to prev
    
    delete Cur;
}

//display list
void print(NodePtr Head){
    NodePtr Cur = Head->next;
    
    while (Cur != Head){ //termination condition // we keep moving // cur == head then we knoww weve gone to the entire list
        cout << Cur->data << " ";
        Cur = Cur->next;
        
    }
    cout << endl;
}




int main() {
    
    NodePtr Head;
    
    //create an empty doubly linked listc
    createHead(Head);
    
    insertNode(Head, 10);
    insertNode(Head, 20);
    insertNode(Head, 30);
    insertNode(Head, 40);
    
    cout << "Original List: ";
    print(Head);
    
    NodePtr Cur = Head->next->next; // point cur to 20
    deleteNode(Cur); // will delete 20 since its thecur
    
    cout << "After Deleting 20: ";
    print(Head);
        
    
    return 0;
}
