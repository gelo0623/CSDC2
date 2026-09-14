//DOUBLY LINKED LISTS
/*
Singly - oneway(H->Null)
Circular - twoway (R/T->)
what if theres something that can remeber what comes before and next// this is doubly // point next adn comes before it
circuar solves the problem that it wont come to an end but goes arount it

a circular dont let you to arbitary
a an advantage of doubly it has a next and before// both directions
cur-> next goes forward cur->prev goes back

singly - only forward
next pointer stores the address of the next one

Circular - uses next but the last node points to the first node since it has no Null
Doubly - has 2 pointers // both directions


Deleting a Node - two way Reconnection
(Cur->prev)->next = Cur->next
(Cur->next)->prev = Cur->prev
delete Cur;

Inserting a Node - maintains pointer relationship
New->next = Cur //point new node to cur
New->prev = Cur->prev // now to prev
Cur->prev = New // now will recognize the new
(New->prev)->next = New

A dummyhead is not an actual data item // doesnt belong in the list/not a node/ just use to arrange the list
// one operation logic to handle empty list


Insertion operation after the dummy node is  added
New->next = Cur;
New->prev = Cur->prev
Cur->prev = New
(New->prev)->next =  New


Insert a Node new in the middle and before Cur
New->next = Cur;
New->prev = Cur->prev;
Cur->prev = New;
(New->prev)->next = New; // same as insert front


insert a node new to empty list with cur pointing to dummy head node
New->next = Cur;
New->prev = Cur->prev;
Cur->prev = New;
(New->pre)->next = New;


*/

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node* prev; //both directions
};

typedef Node* NodePtr;

/*
doubly liked list Operations
insertNode(NodePtr Head, int item)
deleteNode()
*/


//Searching Node
NodePtr searchNode(NodePtr Head, int item) {
    NodePtr Cur = Head->next;
    while(Cur != Head){
        if(Cur->data = item)
        return Cur;
        
        if(Cur->data < item)
        Cur = Cur->next;
        
        else
        break;
    }
    return NULL;
}


// to create dummy head // self preferencing circular stuct
void createHead(NodePtr& Head){
    Head = new Node;
    Head->next = Head; // points to itself in both directions //necessary even if we have an empty list
    Head->prev = Head;
}


void deleteNode(NodePtr Head, int item){
    NodePtr Cur;
    Cur = searchNode(Head, item);
    if (Cur != NULL){
        Cur->prev->next = Cur->next;
        Cur->next->prev = Cur->prev;
        delete Cur;
    }
}

//insert code program for complete insertion code
void insertNode(NodePtr Head, int item){
NodePtr New, Cur;
New = new Node;
New->data = item;

Cur = Head->next;
while(Cur != Head){ //position cur for insertion
    if(Cur->data < item)
    Cur = Cur->next;
    
    else
    break;
}
New->next = Cur;
New->prev = Cur->prev;
Cur->prev = New;
(New->prev)->next = New;

}

//print the whole list




int main () {
    
    
    
    return 0;
}






















