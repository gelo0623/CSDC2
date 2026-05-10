// step 1 + 2 - linked list + arrow keys + pause/play
// compile: g++ realMusicPlayer.cpp -o music -lwinmm

#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")
using namespace std;

class Node {
public:
    string filename;
    string name;
    Node* next;
    Node* prev;

    Node(string f, string n) {
        filename = f; name = n;
        next = nullptr; prev = nullptr;
    }
};

Node* head       = nullptr;
Node* selected   = nullptr;
Node* nowPlaying = nullptr;

bool isPlaying = false;
bool isPaused  = false;
DWORD g_start    = 0;
DWORD g_pausedAt = 0;

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

void togglePause() {
    if (!isPlaying && !isPaused) return;

    if (!isPaused) {
        g_pausedAt = timeGetTime() - g_start;
        PlaySound(NULL, NULL, 0);
        isPaused  = true;
        isPlaying = false;
    } else {
        g_start = timeGetTime() - g_pausedAt;
        PlaySound(nowPlaying->filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        isPaused  = false;
        isPlaying = true;
    }
}

void drawList() {
    cls();
    cout << "=== Song List ===\n\n";

    Node* temp = head;
    int i = 1;
    do {
        cout << (temp == selected ? " >> " : "    ");
        cout << i++ << ". " << temp->name;

        if (temp == nowPlaying) {
            if (isPlaying)     cout << "  [playing]";
            else if (isPaused) cout << "  [paused]";
        }

        cout << "\n";
        temp = temp->next;
    } while (temp != head);

    cout << "\nUP/DOWN = move   ENTER = play   P = pause/play   ESC = exit\n";
}

int main() {
    insertAtEnd("Fallen.wav",   "Fallen");
    insertAtEnd("Lifetime.wav", "Lifetime");
    insertAtEnd("Multi.wav",    "Multi");

    selected = head;

    while (true) {
        drawList();

        int key = _getch();
        if (key == 224) {
            int k2 = _getch();
            if (k2 == 72)      selected = selected->prev; // UP
            else if (k2 == 80) selected = selected->next; // DOWN
        } else if (key == 13) { // ENTER - play
            PlaySound(NULL, NULL, 0);
            PlaySound(selected->filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
            nowPlaying = selected;
            isPlaying  = true;
            isPaused   = false;
            g_start    = timeGetTime();
        } else if (toupper(key) == 'P') { // pause/resume
            togglePause();
        } else if (key == 27) { // ESC - exit
            PlaySound(NULL, NULL, 0);
            return 0;
        }
    }
}
