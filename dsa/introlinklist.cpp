#include <iostream>
using namespace std;

//creating a node struct like place where you can store your data
struct Node {
    int data;
    Node* next; // points to the next node
    

};

//creating nodes aagain like 3 block of nodes that points to another node
Node* n;
Node* t;
Node* h;

n = new Node; // creating a node that is able to point to the next node and you can also store data here
n->data = 1; //the data

// pointing to  another node
n = new Node;
n->data = 2;

// to link these 2 new nodes is
t->next = n;
// now to move the t to the next new nodes
t = t->next;



// create and connect and point to another node;
// create another new node
n = new node;
n->data = 3;

//to connect the prev to the new
t->next = n; // to make conenct the prev node to the new node

// then make a new
n = new node; //new node 
t = t->next; // to make t be on the new node
n->data = 4;
t->next = n; // to connect the prev to new node again;

//to stop it this pointing
n->next = NULL;









