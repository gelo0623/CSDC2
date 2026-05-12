#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

// Added libraries
#include <vector>     // _kbhit(), _getch()

using namespace std;

// Constants
const string CSV_FILE        = "playlist.csv";
const string EXPECTED_HEADER = "Title,Artist,Genre,Year,Duration,AudioFile";

// Nag pa help ako sir sa AI to use colors and UI help lang ah
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"

// Colors
#define BLK         "\033[30m"
#define RED         "\033[31m"
#define GRN         "\033[32m"
#define YLW         "\033[33m"
#define BLU         "\033[34m"
#define MAG         "\033[35m"
#define CYN         "\033[36m"
#define WHT         "\033[37m"

// Bright colors
#define BGRN        "\033[92m"
#define BYLW        "\033[93m"
#define BBLU        "\033[94m"
#define BMAG        "\033[95m"
#define BCYN        "\033[96m"
#define BWHT        "\033[97m"

// Background colors
#define BG_BLK      "\033[40m"
#define BG_BLU      "\033[44m"
#define BG_MAG      "\033[45m"
#define BG_CYN      "\033[46m"
#define BG_BBLK     "\033[100m"

// Box cdraw characters
#define TL  "\xda"   // ┌  
#define TR  "\xbf"   // ┐
#define BL  "\xc0"   // └
#define BR  "\xd9"   // ┘
#define HZ  "\xc4"   // ─
#define VT  "\xb3"   // │
#define LT  "\xc3"   // ├
#define RT  "\xb4"   // ┤


void enableANSI() {

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD dwMode = 0;

    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);

    
    SetConsoleOutputCP(CP_UTF8);
}


void hideCursor() { 
    cout << "\033[?25l";
}


void showCursor() { 
    cout << "\033[?25h"; 

}

// Move cursor to (row, col) — 1-indexed
void gotoXY(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";

}

// Clear Screen
void clearScreen() {
    system("cls");
}

// Sleep Function
void sleepOneSecond() {
    Sleep(1000);

}

// Helper Function
string toLower(string str) {

    for (int i = 0; i < (int)str.length(); i++)

        str[i] = tolower(str[i]);
    return str;


}

// Repeat a character n times
string repeat(string ch, int n) {
    string s = "";

    for (int i = 0; i < n; i++) s += ch;
    return s;
}

// Print a horizontal box line (full width)
void printHLine(int width) {

    cout << CYN << repeat("\xc4", width) << RESET << "\n";

}

// Draw a box around a title header WITH AI HELP
void printHeader(string title, int width = 50) {
    int pad  = (width - 2 - (int)title.length()) / 2;
    int rpad = width - 2 - (int)title.length() - pad;

    cout << CYN << "\xda" << repeat("\xc4", width - 2) << "\xbf" << RESET << "\n";
    cout << CYN << "\xb3" << RESET << repeat(" ", pad) << BOLD << BYLW << title << RESET
    << repeat(" ", rpad)
    << CYN << "\xb3" << RESET << "\n";

    cout << CYN << "\xc0" << repeat("\xc4", width - 2) << "\xd9" << RESET << "\n";
}

// Print a "now playing" bar
void printNowPlayingBar(string title, string artist, int width = 50) {

    cout << BG_BLU << BOLD << BWHT;
    cout << "  \xe2\x99\xab  NOW PLAYING: " << title << " - " << artist;

    int used = 17 + (int)title.length() + 3 + (int)artist.length();

    while (used < width - 2) { cout << " "; used++; }

    cout << "  ";
    cout << RESET << "\n";
}


// ako na gumawa nito sir with your layout na for windows
class Song {
public:
    string title;
    string artist;
    string genre;
    int    year;
    string duration;  // "MM:SS"
    string audioFile; // added this function for the playing and adding off audio files

    Song() { year = 0; }

    Song(string t, string a, string g, int y, string d, string audio = "") {
        title = t; artist = a; genre = g; year = y; duration = d; audioFile = audio;
    }

    // Convert MM:SS total seconds
    int durationInSeconds() const {
        int colonPos = duration.find(":");
        if (colonPos == (int)string::npos) return 0;
        return stoi(duration.substr(0, colonPos)) * 60
        + stoi(duration.substr(colonPos + 1));
    }
};


class Node {
public:
    Song  song;
    Node* next;
    Node* prev;

    Node(Song s) { song = s; next = nullptr; prev = nullptr; }
};


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

        file << "Fallen,Lola Amour,Indie Pop-Rock,2021,3:21,songs/Fallen.wav\n";
        file << "Lifetime,Ben&Ben,Folk-Pop Ballad,2026,4:37,songs/Lifetime.wav\n";
        file << "Multo,Cup of Joe,Pop-Rock Ballad,2024,3:58,songs/Multo.wav\n"; //  changed song instead of pritn i made it played
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
                                stoi(fields[3]), fields[4], fields[5]);
        }
        file.close();
        return count;
    }
};


class MusicPlayer {
private:
    Node*      head;
    Node*      current;
    bool       isPlaying;
    CSVManager csv;

    void playAudio(string path) {
        PlaySound(path.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    }

    void stopAudio() {
        PlaySound(NULL, 0, 0);
    }

    // Print full song details inside a styled card
    void displaySong(Song s) {
        cout << CYN << "  \xc3" << repeat("\xc4", 46) << "\xb4" << RESET << "\n";
        cout << CYN << "  \xb3 " << RESET << BOLD << "Title    : " << RESET << BYLW << s.title    << RESET << "\n";
        cout << CYN << "  \xb3 " << RESET << BOLD << "Artist   : " << RESET << BWHT << s.artist   << RESET << "\n";
        cout << CYN << "  \xb3 " << RESET << BOLD << "Genre    : " << RESET << MAG  << s.genre    << RESET << "\n";
        cout << CYN << "  \xb3 " << RESET << BOLD << "Year     : " << RESET << GRN  << s.year     << RESET << "\n";
        cout << CYN << "  \xb3 " << RESET << BOLD << "Duration : " << RESET << CYN  << s.duration << RESET << "\n";
        cout << CYN << "  \xc0" << repeat("\xc4", 46) << "\xd9" << RESET << "\n";
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
    void runTimer(Song s) {
        int total   = s.durationInSeconds();
        int elapsed = 0;
        int barWidth = 30;

        cout << "\n";
        cout << DIM << "  Press any key to stop...\n" << RESET << "\n";

        while (elapsed <= total) {
            int eMin = elapsed / 60, eSec = elapsed % 60;
            int tMin = total   / 60, tSec = total   % 60;
            int filled = (total > 0) ? (elapsed * barWidth / total) : barWidth;

            cout << "\r  " << CYN
                 << (eMin < 10 ? "0" : "") << eMin << ":"
                 << (eSec < 10 ? "0" : "") << eSec
                 << RESET << "  " << CYN << "[" << RESET;

            for (int i = 0; i < barWidth; i++) {
                if (i < filled)
                    cout << BGRN << "#" << RESET;
                else
                    cout << DIM << "-" << RESET;
            }

            cout << CYN << "]" << RESET << "  "
                 << DIM
                 << (tMin < 10 ? "0" : "") << tMin << ":"
                 << (tSec < 10 ? "0" : "") << tSec
                 << RESET << "   " << flush;

            if (elapsed == total) break;

            bool stopped = false;
            for (int tick = 0; tick < 10; tick++) {
                if (_kbhit()) {
                    _getch();
                    stopped = true;
                    break;
                }
                Sleep(100);
            }
            if (stopped) {
                cout << "\n\n  " << BYLW << "[STOPPED]" << RESET << "\n";
                return;
            }
            elapsed++;
        }

        cout << "\n\n  " << BGRN << "[DONE] Finished playing." << RESET << "\n";
    }
\
    int arrowSelect(string items[], int count, int startSel = 0) { // up and down keys and esc keys
        int sel = startSel;
        hideCursor();

        while (true) {
        
            cout << "\033[" << count << "A";

            for (int i = 0; i < count; i++) {
                if (i == sel) {
                    cout << "  " << BG_BBLK << BYLW << BOLD
                         << " >> " << items[i]
                         << repeat(" ", 44 - (int)items[i].length())
                         << RESET << "\n";
                } else {
                    cout << "       " << DIM << items[i] << RESET << "\n";
                }
            }

            int ch = _getch();
            if (ch == 0 || ch == 224) {   // arrow key prefix
                int arrow = _getch();
                if (arrow == 72) sel = (sel - 1 + count) % count;  // UP
                if (arrow == 80) sel = (sel + 1) % count;           // DOWN
            } else if (ch == 13) {  // ENTER
                showCursor();
                return sel;
            } else if (ch == 27) {  // ESC
                showCursor();
                return -1;
            }
        }
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
        printHeader("  Add New Song  ", 50);
        cout << "\n";

        string title, artist, genre, duration;
        int year;

        cout << CYN << "  Title       : " << RESET; getline(cin, title);
        cout << CYN << "  Artist      : " << RESET; getline(cin, artist);

        if (csv.isDuplicate(title, artist)) {
            cout << "\n  " << RED << "[!] \"" << title << "\" by " << artist
                 << " is already in the playlist!\n"
                 << "      Duplicate was not added.\n" << RESET;
            return;
        }

        cout << CYN << "  Genre       : " << RESET; getline(cin, genre);
        cout << CYN << "  Year        : " << RESET; cin >> year; cin.ignore();
        cout << CYN << "  Duration    : " << RESET; getline(cin, duration);

        Song newSong(title, artist, genre, year, duration);
        insertAtEnd(newSong);
        csv.saveSong(newSong);

        cout << "\n  " << BGRN << "[+] Song added successfully!" << RESET << "\n\n";
        displaySong(newSong);
    }

    // 2. Play Current Song
    void playSong() {
        clearScreen();
        printHeader("  Now Playing  ", 50);
        cout << "\n";

        if (!head) { cout << "  " << RED << "No songs in playlist!\n" << RESET; return; }

        if (!isPlaying) {
            current   = head;
            isPlaying = true;
        }

        printNowPlayingBar(current->song.title, current->song.artist, 50);
        cout << "\n";
        displaySong(current->song);
        playAudio(current->song.audioFile);
        runTimer(current->song);
        stopAudio();
    }

    // 3. Next Song
    void nextSong() {
        clearScreen();
        printHeader("  Next Song  ", 50);
        cout << "\n";

        if (!head) { cout << "  " << RED << "No songs in playlist!\n" << RESET; return; }

        if (!isPlaying) {
            current   = head;
            isPlaying = true;
            cout << "  " << DIM << "[No song was playing. Starting from the first song.]\n\n" << RESET;
        } else {
            current = current->next;
        }

        printNowPlayingBar(current->song.title, current->song.artist, 50);
        cout << "\n";
        displaySong(current->song);

        cout << "\n  " << CYN << "-- Linked List View --\n" << RESET;
        cout << "  " << DIM << "PREV : " << current->prev->song.title << RESET << "\n";
        cout << "  " << BYLW << BOLD << "NOW  : " << current->song.title << "  <-- current\n" << RESET;
        cout << "  " << DIM << "NEXT : " << current->next->song.title << RESET << "\n\n";

        playAudio(current->song.audioFile);
        runTimer(current->song);
        stopAudio();
    }

    // 4. Previous Song
    void prevSong() {
        clearScreen();
        printHeader("  Previous Song  ", 50);
        cout << "\n";

        if (!head) { cout << "  " << RED << "No songs in playlist!\n" << RESET; return; }

        if (!isPlaying) {
            cout << "  " << BYLW << "[!] No previous song — nothing has been played yet.\n"
                 << "      Play or skip to a song first!\n" << RESET;
            return;
        }

        current = current->prev;

        printNowPlayingBar(current->song.title, current->song.artist, 50);
        cout << "\n";
        displaySong(current->song);

        cout << "\n  " << CYN << "-- Linked List View --\n" << RESET;
        cout << "  " << DIM << "PREV : " << current->prev->song.title << RESET << "\n";
        cout << "  " << BYLW << BOLD << "NOW  : " << current->song.title << "  <-- current\n" << RESET;
        cout << "  " << DIM << "NEXT : " << current->next->song.title << RESET << "\n\n";

        playAudio(current->song.audioFile);
        runTimer(current->song);
        stopAudio();
    }

    // 5. Show Playlist  (with arrow-key song picker)
    void showPlaylist() {
        clearScreen();
        printHeader("  Playlist  ", 50);
        cout << "\n";

        if (!head) { cout << "  " << RED << "Playlist is empty!\n" << RESET; return; }

        int n = countSongs();
        string items[500];
        Node*  nodes[500];
        Node*  temp = head;
        int    startSel = 0;

        for (int i = 0; i < n; i++) {
            string marker = (isPlaying && temp == current) ? "\xe2\x99\xab " : "  ";
            items[i] = marker + temp->song.title + " - " + temp->song.artist
                     + "  [" + temp->song.duration + "]";
            nodes[i] = temp;
            if (isPlaying && temp == current) startSel = i;
            temp = temp->next;
        }

        cout << "  " << DIM << "Use UP/DOWN arrows, ENTER to play, ESC to go back\n" << RESET << "\n";

        
        for (int i = 0; i < n; i++) {
            if (i == startSel)
                cout << "  " << BG_BBLK << BYLW << BOLD << " >> " << items[i]
                     << repeat(" ", 44 - (int)items[i].length()) << RESET << "\n";
            else
                cout << "       " << DIM << items[i] << RESET << "\n";
        }

        int sel = arrowSelect(items, n, startSel);

        if (sel == -1) return; // ESC pressed

        // Play the selected song
        current   = nodes[sel];
        isPlaying = true;

        clearScreen();
        printHeader("  Now Playing  ", 50);
        cout << "\n";
        printNowPlayingBar(current->song.title, current->song.artist, 50);
        cout << "\n";
        displaySong(current->song);
        playAudio(current->song.audioFile);
        runTimer(current->song);
        stopAudio();
    }

    // 6. Play Random Song
    void playRandom() {
        clearScreen();
        printHeader("  Random Song  ", 50);
        cout << "\n";

        if (!head) { cout << "  " << RED << "Playlist is empty!\n" << RESET; return; }

        int n = countSongs();
        int r = rand() % n;
        Node* temp = head;
        for (int i = 0; i < r; i++) temp = temp->next;

        current   = temp;
        isPlaying = true;

        printNowPlayingBar(current->song.title, current->song.artist, 50);
        cout << "\n";
        displaySong(current->song);
        playAudio(current->song.audioFile);
        runTimer(current->song);
        stopAudio();
    }

    // 7. Shuffle Playlist
    void shufflePlaylist() {
        clearScreen();
        printHeader("  Shuffle Playlist  ", 50);
        cout << "\n";

        if (!head) { cout << "  " << RED << "Playlist is empty!\n" << RESET; return; }

        shuffleList();

        cout << "  " << BGRN << "[+] Playlist shuffled! New order:\n\n" << RESET;
        Node* temp = head;
        int   num  = 1;
        do {
            cout << "  " << CYN << num++ << ". " << RESET
                 << BOLD << "\"" << temp->song.title << "\"" << RESET
                 << DIM << " by " << RESET << temp->song.artist << "\n";
            temp = temp->next;
        } while (temp != head);

        cout << "\n  " << DIM << "Now playing from the top...\n\n" << RESET;
        isPlaying = true;
        printNowPlayingBar(current->song.title, current->song.artist, 50);
        cout << "\n";
        displaySong(current->song);
        playAudio(current->song.audioFile);
        runTimer(current->song);
        stopAudio();
    }

    // 8. Search Song  (live search with arrow-key result picker)
    void searchSong() {
        string search = "";
        int    sel    = 0;   

        while (true) {
            clearScreen();
            printHeader("  Search a Song  ", 50);
            cout << "\n";
            cout << "  " << CYN << "Search: " << RESET << BOLD << search << RESET << "_\n";
            cout << "  " << DIM << "(Type to search | UP/DOWN to highlight | ENTER to play | ESC to exit)\n" << RESET;
            printHLine(50);
            cout << "\n";

            // Collect matching nodes
            Node*  matchNodes[500];
            string matchItems[500];
            int    matchCount = 0;

            if (head) {
                Node* temp = head;
                do {
                    string title = toLower(temp->song.title);
                    if (search.empty() || title.find(toLower(search)) != string::npos) {
                        matchNodes[matchCount] = temp;
                        matchItems[matchCount] = temp->song.title + " - " + temp->song.artist
                                               + "  [" + temp->song.duration + "]";
                        matchCount++;
                    }
                    temp = temp->next;
                } while (temp != head);
            }

            // Clamp selection index
            if (matchCount == 0) sel = 0;
            else if (sel >= matchCount) sel = matchCount - 1;
            else if (sel < 0) sel = 0;

            // Display results
            if (matchCount == 0) {
                cout << "  " << RED << "No songs found.\n" << RESET;
            } else {
                for (int i = 0; i < matchCount; i++) {
                    if (i == sel) {
                        cout << "  " << BG_BBLK << BYLW << BOLD
                             << " >> " << matchItems[i]
                             << repeat(" ", 44 - (int)matchItems[i].length())
                             << RESET << "\n";
                    } else {
                        cout << "       " << DIM << matchItems[i] << RESET << "\n";
                    }
                }
            }

            
            int ch = _getch();

            if (ch == 0 || ch == 224) {          
                int arrow = _getch();
                if (arrow == 72 && matchCount > 0) sel = (sel - 1 + matchCount) % matchCount;  // UP
                if (arrow == 80 && matchCount > 0) sel = (sel + 1) % matchCount;               // DOWN
            } else if (ch == 13) {               // ENTER — play highlighted song
                if (matchCount > 0) {
                    current   = matchNodes[sel];
                    isPlaying = true;

                    clearScreen();
                    printHeader("  Now Playing  ", 50);
                    cout << "\n";
                    printNowPlayingBar(current->song.title, current->song.artist, 50);
                    cout << "\n";
                    displaySong(current->song);
                    playAudio(current->song.audioFile);
                    runTimer(current->song);
                    stopAudio();
                }
                return;
            } else if (ch == 27) {               // ESC — exit search
                showCursor();
                return;
            } else if (ch == 8) {                // BACKSPACE
                if (!search.empty()) {
                    search.pop_back();
                    sel = 0;
                }
            } else if (isprint(ch)) {            // printable character
                search += (char)ch;
                sel = 0;
            }
        }
    }
};


void menu() {
    srand(time(0));
    enableANSI();
    MusicPlayer player;

    const int MENU_COUNT = 9;
    string menuItems[MENU_COUNT] = {
        "Add Song",
        "Play Current Song",
        "Next Song",
        "Previous Song",
        "Show Playlist",
        "Play Random Song",
        "Shuffle Playlist",
        "Search Song",
        "Exit"
    };

    int sel = 0;
    hideCursor();

    while (true) {
        clearScreen();

        // ── Banner ──────────────────────────────────────────
        cout << "\n";
        cout << CYN << "  \xda" << repeat("\xc4", 48) << "\xbf" << RESET << "\n";
        cout << CYN << "  \xb3" << RESET
             << BG_BLU << BOLD << BWHT
             << "          \xe2\x99\xab  MUSIC PLAYER  \xe2\x99\xab           "
             << RESET
             << CYN << "\xb3" << RESET << "\n";
        cout << CYN << "  \xc0" << repeat("\xc4", 48) << "\xd9" << RESET << "\n\n";

        cout << "  " << DIM << "Use UP/DOWN arrows + ENTER to select\n" << RESET << "\n";

        // ── Menu items ──────────────────────────────────────
        for (int i = 0; i < MENU_COUNT; i++) {
            string num = (i < MENU_COUNT - 1) ? to_string(i + 1) + ". " : "0. ";
            if (i == sel) {
                cout << "  " << BG_BBLK << BYLW << BOLD
                     << " >> " << num << menuItems[i]
                     << repeat(" ", 40 - (int)menuItems[i].length() - (int)num.length())
                     << RESET << "\n";
            } else {
                cout << "       " << DIM << num << menuItems[i] << RESET << "\n";
            }
        }

        cout << "\n";
        cout << CYN << "  " << repeat("\xc4", 48) << RESET << "\n";


        int ch = _getch();

        if (ch == 0 || ch == 224) {
            int arrow = _getch();
            if (arrow == 72) sel = (sel - 1 + MENU_COUNT) % MENU_COUNT;  // UP
            if (arrow == 80) sel = (sel + 1) % MENU_COUNT;               // DOWN
            continue;
        }

        if (ch == 13) {   // ENTER
            showCursor();
            int choice = sel + 1;          // 1-based; Exit is item 9 → choice 9
            if (choice == MENU_COUNT) {    // Exit
                clearScreen();
                cout << "\n  " << BGRN << "Exiting Music Player. Goodbye!\n" << RESET << "\n";
                break;
            }

            switch (choice) {
                case 1: player.addSong();         break;
                case 2: player.playSong();        break;
                case 3: player.nextSong();        break;
                case 4: player.prevSong();        break;
                case 5: player.showPlaylist();    break;
                case 6: player.playRandom();      break;
                case 7: player.shufflePlaylist(); break;
                case 8: player.searchSong();      break;
            }

            cout << "\n  " << DIM << "Press Enter to go back to menu..." << RESET;
            cin.get();
            hideCursor();
        }

        if (ch >= '1' && ch <= '8') {
            sel = ch - '1';
        } else if (ch == '0') {
            sel = MENU_COUNT - 1;
        }
    }

    showCursor();
}

int main() {
    menu();
    return 0;
}
