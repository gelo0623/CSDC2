// step 1 - linked list + arrow key navigation
// compile: g++ realMusicPlayer.cpp -o music -lwinmm

#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

// Node for circular doubly linked list (same as your original)
class Node {
public:
    string filename;
    string name;
    Node* next;
    Node* prev;

    Node(string f, string n) {
        filename = f;
        name = n;
        next = nullptr;
        prev = nullptr;
    }
};

// the list
Node* head = nullptr;
Node* selected = nullptr;  // where the >> is
Node* nowPlaying = nullptr; // what's actually playing

// insert at end (same logic as your original)
void insertAtEnd(string filename, string name) {
    Node* newNode = new Node(filename, name);
    if (!head) {
        newNode->next = newNode;
        newNode->prev = newNode;
        head = newNode;
    } else {
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
}

void cls() { system("cls"); }

void drawList() {
    cls();
    cout << "=== Song List ===\n\n";

    Node* temp = head;
    int i = 1;
    do {
        if (temp == selected)
            cout << " >> ";
        else
            cout << "    ";

        cout << i++ << ". " << temp->name;

        if (temp == nowPlaying)
            cout << "  [playing]";

        cout << "\n";
        temp = temp->next;
    } while (temp != head);

    cout << "\nUP/DOWN = move   ENTER = play   ESC = exit\n";
}

int main() {
    // load your songs
    insertAtEnd("Fallen.wav",   "Fallen");
    insertAtEnd("Lifetime.wav", "Lifetime");
    insertAtEnd("Multi.wav",    "Multi");

    selected = head; // start >> at first song

    while (true) {
        drawList();

        int key = _getch();
        if (key == 224) {
            int k2 = _getch();
            if (k2 == 72) {        // UP
                selected = selected->prev;
            } else if (k2 == 80) { // DOWN
                selected = selected->next;
            }
        } else if (key == 13) { // ENTER - play selected
            PlaySound(NULL, NULL, 0);
            PlaySound(selected->filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            nowPlaying = selected;
        } else if (key == 27) { // ESC - exit
            PlaySound(NULL, NULL, 0);
            return 0;
        }
    }
}
