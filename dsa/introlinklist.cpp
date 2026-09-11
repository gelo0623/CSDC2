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


n->data = 1;
h = n;

n2->data = 2;
n->next = n2; // to move the first node to the second node 

n3->data = 3;
n2->next = n3; // to move second node to third

n3->next = NULL;

//say that we want to start at the new node or the last and make it point to the firts
n4->next = h // since n is h  
h = n4 //make n4 the head since we start here

//say youre gonna delete first node or you will not start from it or so
node* temp = h;//save the location before moving h 
h = h->next // no h is at b and will start at b / this just makes A not part of the sequence anymore but A is still there
    // if we do this first we lost the only address that points to A, A is gone and unreachable and we can never call delete on it again// once you move you can never go back
delete temp // removes temp / destroys the node completely









