#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

// Added libraries
#include <vector>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

// _WIN32 Libraries
#include <windows.h>
#include <conio.h>     // _kbhit(), _getch()

using namespace std;

// Constants
const string CSV_FILE        = "playlist.csv";
const string EXPECTED_HEADER = "Title,Artist,Genre,Year,Duration,AudioFile";

// Clear Screen
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Sleep Function
void sleepOneSecond() {
#ifdef _WIN32
    Sleep(1000);
#else
    sleep(1);
#endif
}

// Helper Function
string toLower(string str) {
    for (int i = 0; i < (int)str.length(); i++)
        str[i] = tolower(str[i]);
    return str;
}

// CLASS: Song
class Song {
public:
    string title;
    string artist;
    string genre;
    int    year;
    string duration;  // "MM:SS"
    // ADDED
    string audioFile;

    Song() { year = 0; }

    Song(string t, string a, string g, int y, string d, string audio = "") { // added string audio = ""
        title = t; artist = a; genre = g; year = y; duration = d; audioFile = audio;
    }

    // Convert "MM:SS" → total seconds
    int durationInSeconds() const {
        int colonPos = duration.find(":");
        if (colonPos == (int)string::npos) return 0;
        return stoi(duration.substr(0, colonPos)) * 60
             + stoi(duration.substr(colonPos + 1));
    }
};

// CLASS: Node  (circular doubly linked list)
class Node {
public:
    Song  song;
    Node* next;
    Node* prev;

    Node(Song s) { song = s; next = nullptr; prev = nullptr; }
};

// CLASS: CSVManager
class CSVManager {
public:
    // Split a line into exactly fieldCount comma-separated tokens
    bool parseLine(string line, string fields[], int fieldCount) {
        int idx = 0;
        string token = "";
        for (int i = 0; i <= (int)line.length(); i++) {
            if (i == (int)line.length() || line[i] == ',') {
                if (idx >= fieldCount) return false;
                fields[idx++] = token;
                token = "";
            } else {
                token += line[i];
            }
        }
        return idx == fieldCount;
    }

    void writeDefaultSongs() {
        ofstream file(CSV_FILE);
        if (!file.is_open()) { cout << "Error: Cannot create CSV.\n"; return; }
        file << EXPECTED_HEADER << "\n";

        // Songs by Toto
        file << "Fallen,Lola Amour,Indie Pop-Rock,2021,3:21,songs/Fallen.wav\n"; //ADDED
        file << "Lifetime,Ben&Ben,Folk-Pop Ballad,2026,4:37,songs/Lifetime.wav\n";
        file << "Multo,Cup of Joe,Pop-Rock Ballad,2024,3:58,songs/Multo.wav\n";
        file.close();
    }

    void createDefaultCSV() {
        ifstream checkFile(CSV_FILE);
        if (checkFile.is_open()) {
            string header;
            getline(checkFile, header);
            checkFile.close();
            if (header == EXPECTED_HEADER) return;
            cout << "[!] Old CSV format detected. Recreating playlist.csv...\n";
        }
        writeDefaultSongs();
        cout << "Default playlist CSV created: " << CSV_FILE << "\n";
    }

    bool isDuplicate(string title, string artist) {
        ifstream file(CSV_FILE);
        if (!file.is_open()) return false;
        string line;
        getline(file, line);
        while (getline(file, line)) {
            if (line.empty()) continue;
            string fields[6];
            if (!parseLine(line, fields, 6)) continue;
            if (toLower(fields[0]) == toLower(title) &&
                toLower(fields[1]) == toLower(artist)) {
                file.close(); return true;
            }
        }
        file.close(); return false;
    }

    void saveSong(Song s) {
        ofstream file(CSV_FILE, ios::app);
        if (!file.is_open()) { cout << "Error: Cannot write CSV.\n"; return; }
        file << s.title   << "," << s.artist << "," << s.genre << ","
             << s.year    << "," << s.duration << "," << s.audioFile << "\n";
        file.close();
    }

    int loadSongs(Song songs[], int maxSongs) {
        ifstream file(CSV_FILE);
        if (!file.is_open()) { cout << "Error: Cannot open CSV.\n"; return 0; }
        string line;
        getline(file, line); // skip header
        int count = 0;
        while (getline(file, line) && count < maxSongs) {
            if (line.empty()) continue;
            string fields[6];
            if (!parseLine(line, fields, 6)) continue;
            songs[count++] = Song(fields[0], fields[1], fields[2],
                                  stoi(fields[3]), fields[4], fields[5]); //cahnged
        }
        file.close();
        return count;
    }
};

// CLASS: MusicPlayer
class MusicPlayer {
private:
    Node*      head;
    Node*      current;
    bool       isPlaying;  // true only after user picks a song to play
    CSVManager csv;

    // added to play songs
    void playAudio(string path) {
        
        PlaySound(path.c_str(), NULL, SND_FILENAME | SND_ASYNC); // added to play the songs
    }

    void stopAudio() {
        PlaySound(NULL, 0, 0);
    }

    // Print full song details
    void displaySong(Song s) {
        cout << "  Title    : " << s.title    << "\n";
        cout << "  Artist   : " << s.artist   << "\n";
        cout << "  Genre    : " << s.genre    << "\n";
        cout << "  Year     : " << s.year     << "\n";
        cout << "  Duration : " << s.duration << "\n";
    }

    // Count all nodes
    int countSongs() {
        if (!head) return 0;
        int n = 0;
        Node* t = head;
        do { n++; t = t->next; } while (t != head);
        return n;
    }

    // Insert at end of circular list
    void insertAtEnd(Song s) {
        Node* newNode = new Node(s);
        if (!head) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        } else {
            Node* tail    = head->prev;
            tail->next    = newNode;
            newNode->prev = tail;
            newNode->next = head;
            head->prev    = newNode;
        }
    }

    // Fisher-Yates shuffle on the linked list
    void shuffleList() {
        int n = countSongs();
        if (n <= 1) return;

        Node* nodes[500];
        Node* t = head;
        for (int i = 0; i < n; i++) { nodes[i] = t; t = t->next; }

        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            Song tmp       = nodes[i]->song;
            nodes[i]->song = nodes[j]->song;
            nodes[j]->song = tmp;
        }

        for (int i = 0; i < n; i++) {
            nodes[i]->next = nodes[(i + 1) % n];
            nodes[i]->prev = nodes[(i - 1 + n) % n];
        }

        head      = nodes[0];
        current   = head;
        isPlaying = false;
    }

    // Live playback timer
    // Counts up second by second with a progress bar.
    // On any keypress the timer stops immediately.
    void runTimer(Song s) {
        int total   = s.durationInSeconds();
        int elapsed = 0;
        int barWidth = 30;

        cout << "\n  Press any key to stop...\n\n";

    while (elapsed <= total) {
        int eMin = elapsed / 60, eSec = elapsed % 60;
        int tMin = total   / 60, tSec = total   % 60;
        int filled = (total > 0) ? (elapsed * barWidth / total) : barWidth;

        cout << "\r  "
             << (eMin < 10 ? "0" : "") << eMin << ":"
             << (eSec < 10 ? "0" : "") << eSec
             << "  [";
        for (int i = 0; i < barWidth; i++) cout << (i < filled ? '#' : '-');
            cout << "]  "
            << (tMin < 10 ? "0" : "") << tMin << ":"
            << (tSec < 10 ? "0" : "") << tSec
            << "   " << flush;

        if (elapsed == total) break;

        // Check for keypress each 100ms for 10 iterations = 1 second
        bool stopped = false;
        for (int tick = 0; tick < 10; tick++) {
            if (_kbhit()) {
                _getch(); // consume the key
                stopped = true;
                break;
            }
            Sleep(100);
        }
        if (stopped) {
            cout << "\n\n  [STOPPED]\n";
            return;
        }
        elapsed++;
    }

    cout << "\n\n  [DONE] Finished playing.\n";
    }

public:
    MusicPlayer() {
        head      = nullptr;
        current   = nullptr;
        isPlaying = false;
        csv.createDefaultCSV();
        loadFromCSV();
    }

    void loadFromCSV() {
        Song songs[500];
        int count = csv.loadSongs(songs, 500);
        for (int i = 0; i < count; i++) insertAtEnd(songs[i]);
    }

    // 1. Add Song
    void addSong() {
        clearScreen();
        cout << "=== Add Song ===\n\n";

        string title, artist, genre, duration;
        int year;

        cout << "Enter song title      : "; getline(cin, title);
        cout << "Enter artist name     : "; getline(cin, artist);

        if (csv.isDuplicate(title, artist)) {
            cout << "\n[!] \"" << title << "\" by " << artist
                 << " is already in the playlist!\n"
                 << "    Duplicate was not added.\n";
            return;
        }

        cout << "Enter genre           : "; getline(cin, genre);
        cout << "Enter release year    : "; cin >> year; cin.ignore();
        cout << "Enter duration (MM:SS): "; getline(cin, duration);

        Song newSong(title, artist, genre, year, duration);
        insertAtEnd(newSong);
        csv.saveSong(newSong);

        cout << "\n[+] Song added successfully!\n\n";
        displaySong(newSong);
    }

    // 2. Play Current Song
    void playSong() {
        clearScreen();
        cout << "=== Now Playing ===\n\n";

        if (!head) { cout << "No songs in playlist!\n"; return; }

        if (!isPlaying) {
            current   = head;
            isPlaying = true;
        }

        displaySong(current->song);
        playAudio(current->song.audioFile); // added to play and pause
        runTimer(current->song);
        stopAudio();
    }

    // 3. Next Song
    // Linked list showcase: follow ->next pointer.
    // If nothing is playing yet, start from head (no previous exists).
    void nextSong() {
        clearScreen();
        cout << "=== Next Song ===\n\n";

        if (!head) { cout << "No songs in playlist!\n"; return; }

        if (!isPlaying) {
            current   = head;
            isPlaying = true;
            cout << "  [No song was playing. Starting from the first song.]\n\n";
        } else {
            current = current->next; // Follow the ->next pointer
        }

        displaySong(current->song);

        cout << "\n  -- Linked List View --\n";
        cout << "  PREV : " << current->prev->song.title << "\n";
        cout << "  NOW  : " << current->song.title << "  <-- current\n";
        cout << "  NEXT : " << current->next->song.title << "\n\n";

        playAudio(current->song.audioFile); // added to play and pause
        runTimer(current->song);
        stopAudio();
    }

    // 4. Previous Song
    // Linked list showcase: follow ->prev pointer.
    // If nothing is playing, block — there is no history yet.
    void prevSong() {
        clearScreen();
        cout << "=== Previous Song ===\n\n";

        if (!head) { cout << "No songs in playlist!\n"; return; }

        if (!isPlaying) {
            cout << "  [!] No previous song — nothing has been played yet.\n";
            cout << "      Play or skip to a song first!\n";
            return;
        }

        current = current->prev; // Follow the ->prev pointer

        displaySong(current->song);

        cout << "\n  -- Linked List View --\n";
        cout << "  PREV : " << current->prev->song.title << "\n";
        cout << "  NOW  : " << current->song.title << "  <-- current\n";
        cout << "  NEXT : " << current->next->song.title << "\n\n";

       playAudio(current->song.audioFile); // added to play and pause
        runTimer(current->song);
        stopAudio();
    }

    // 5. Show Playlist
    void showPlaylist() {
        clearScreen();
        cout << "=== Playlist ===\n\n";

        if (!head) { cout << "Playlist is empty!\n"; return; }

        Node* temp = head;
        int   num  = 1;
        do {
            cout << (isPlaying && temp == current ? " >> " : "    ");
            cout << num++ << ". \""   << temp->song.title
                 << "\" by "          << temp->song.artist
                 << "  |  "           << temp->song.genre
                 << "  |  "           << temp->song.year
                 << "  |  "           << temp->song.duration << "\n";
            temp = temp->next;
        } while (temp != head);

        if (!isPlaying)
            cout << "\n  (No song is currently selected.)\n";
    }

    // 6. Play Random Song
    void playRandom() {
        clearScreen();
        cout << "=== Random Song ===\n\n";

        if (!head) { cout << "Playlist is empty!\n"; return; }

        int n = countSongs();
        int r = rand() % n;
        Node* temp = head;
        for (int i = 0; i < r; i++) temp = temp->next;

        current   = temp;
        isPlaying = true;

        displaySong(current->song);
        playAudio(current->song.audioFile); // added to play and pause
        runTimer(current->song);
        stopAudio();
    }

    // 7. Shuffle Playlist
    void shufflePlaylist() {
        clearScreen();
        cout << "=== Shuffle Playlist ===\n\n";

        if (!head) { cout << "Playlist is empty!\n"; return; }

        shuffleList();

        cout << "  [+] Playlist shuffled! New order:\n\n";
        Node* temp = head;
        int   num  = 1;
        do {
            cout << "  " << num++ << ". \"" << temp->song.title << "\" by " << temp->song.artist << "\n";
            temp = temp->next;
        } while (temp != head);

        cout << "\n  Now playing from the top...\n\n";
        isPlaying = true;
        displaySong(current->song);
        playAudio(current->song.audioFile); // added to play and pause
        runTimer(current->song);
        stopAudio();
    }

    // LIVE SEARCG
    void searchSong () {  // added search functtion
        
        string search = "";

        while (true) {
            clearScreen();
            cout << "SEARCH A SONG" << endl;
            cout << "Search: " << search << "\n\n";
            Node* temp = head;
            bool found = false;

            if (head) {
                do {
                    string title = toLower(temp->song.title);
                    
                    if (title.find(toLower(search)) != string::npos) {
                        found = true;

                        cout << ">> " << temp->song.title << " - " << temp->song.artist <<  "\n";
                    }

                    temp = temp->next;
                }
                while (temp != head);
            }
        }

        if (!found)
        cout << "No songs found.\n";

        char ch = _getch();

        if (ch == 13)
        break;


        else if (ch == 8) {
            if (!search.empty())
            search.pop_back();
        }

        else if (isprint(ch)){
            search += ch;
        }
    }
};

// Main Menu
void menu() {
    srand(time(0));
    MusicPlayer player;

    int choice;
    do {
        clearScreen();
        cout << "=== Music Player ===\n";
        cout << "1. Add Song\n";
        cout << "2. Play Current Song\n";
        cout << "3. Next Song\n";
        cout << "4. Previous Song\n";
        cout << "5. Show Playlist\n";
        cout << "6. Play Random Song\n";
        cout << "7. Shuffle Playlist\n";
        cout << "8. Search Song\n"; // added search function
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: player.addSong();         break;
            case 2: player.playSong();        break;
            case 3: player.nextSong();        break;
            case 4: player.prevSong();        break;
            case 5: player.showPlaylist();    break;
            case 6: player.playRandom();      break;
            case 7: player.shufflePlaylist(); break;
            case 8: player.searchSong();      break;
            case 0:
                clearScreen();
                cout << "Exiting Music Player. Goodbye!\n";
                break;
            default:
                clearScreen();
                cout << "Invalid choice! Please try again.\n";
        }

        if (choice != 0) {
            cout << "\nPress Enter to go back to menu...";
            cin.get();
        }

} while (choice != 0);
}

int main() {
    menu();
    return 0;

}
