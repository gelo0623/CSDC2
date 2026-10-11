#include <iostream>
using namespace std;

//LINKED LIST IMPLEMENTATION OF Stack
struct Node{
    int data;
    Node* next;
};

class Stack{
    private:
        Node* top;

    public:
        Stack(){
            top = nullptr; //empty condition
        }
        bool isEmpty(){
            return top == nullptr;
        }
        void push (int value){ // [data - link] push 30
            Node* newNode = new Node; //linked list:[30] [20] [10] [NULL] O(1)
            newNode->data = value;
            newNode->next = top; //array: [10][20][30]

            top = newNode;
        }
        int pop(){
            if(isEmpty()){
                cout << "Stack Underflow\n";
                return -1;
            }
            Node* temp = top;
            int value = top->data;
            top = top->next;
            delete temp;
            return value;
        }
        int peek(){
            if (isEmpty()){
                return -1;
            }
            return top->data;
        }
};

int main (){
    Stack s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << s.pop() << endl;
    cout << s.peek() << endl;

    return 0;
}
