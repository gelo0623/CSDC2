#include <iostream>
using namespace std;
const int MAX = 5; // [] [] [] [] []

class Stack {
    private:
    int arr[MAX];
    int top;

    public:
    Stack(){
        top = -1;
    }

    bool isEmpty(){
        return top == -1;
    }

    bool isFull(){
        return top == MAX - 1;
    }

    void push (int value){
        if (isFull()){
            cout << "Stack Overflow\n";
            return;
        }
        top++; //push 10
        arr[top] = value;
    }

    int pop(){
        if (isEmpty()){
            cout << "Stack Underflow\n";
            return -1;
        }
        int value = arr[top];
        top--;

        return value;
    }

    int peek(){
        if (isEmpty())
            return -1;
        return arr[top];
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
