// ============================================================
// realMusicPlayer.cpp
// Terminal Music Player — Full Featured + Live Search
// Windows only (conio.h + winmm)
//
// Compile:  g++ realMusicPlayer.cpp -o music -lwinmm
// Run:      music.exe
//
// SCREENS:
//   Main Menu, Library, Now Playing, Search, Add Song, Delete Song
//
// SEARCH:
//   Type to filter live — arrow down to highlight result — Enter to play
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// ════════════════════════════════════════════════════════════
//  ANSI COLORS
// ════════════════════════════════════════════════════════════
#define R       "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"
#define CY      "\033[38;5;51m"
#define CY2     "\033[38;5;87m"
#define YL      "\033[38;5;220m"
#define GN      "\033[38;5;82m"
#define GN2     "\033[38;5;48m"
#define OR      "\033[38;5;208m"
#define PK      "\033[38;5;213m"
#define RD      "\033[38;5;203m"
#define W       "\033[38;5;255m"
#define LG      "\033[38;5;250m"
#define DG      "\033[38;5;240m"
#define MG      "\033[38;5;245m"
#define BL      "\033[38;5;117m"
#define BG_SEL  "\033[48;5;234m"
#define BG_NOW  "\033[48;5;22m"
#define BG_SRCH "\033[48;5;17m"   // dark blue bg for search highlight

// ════════════════════════════════════════════════════════════
//  CONSOLE HELPERS
// ════════════════════════════════════════════════════════════
void initConsole() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD m = 0;
    GetConsoleMode(h, &m);
    SetConsoleMode(h, m | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    SetConsoleTitleA("RealMusicPlayer");
}

void cls()        { system("cls"); }
void hideCursor() { cout << "\033[?25l"; }
void showCursor() { cout << "\033[?25h"; }

void printLine(char c, int n, const char* color = DG) {
    cout << color;
    for (int i = 0; i < n; i++) cout << c;
    cout << R;
}

string centerStr(const string& s, int width) {
    int pad = (width - (int)s.size()) / 2;
    if (pad < 0) pad = 0;
    return string(pad, ' ') + s;
}

// Case-insensitive string contains check
bool containsCI(const string& haystack, const string& needle) {
    if (needle.empty()) return true;
    string h = haystack, n = needle;
    transform(h.begin(), h.end(), h.begin(), ::tolower);
    transform(n.begin(), n.end(), n.begin(), ::tolower);
    return h.find(n) != string::npos;
}

// ════════════════════════════════════════════════════════════
//  DURATION TRACKING
// ════════════════════════════════════════════════════════════
DWORD g_startTime    = 0;
DWORD g_pausedAt     = 0;
DWORD g_songDuration = 0;

DWORD getWavDuration(const string& filename) {
    ifstream f(filename, ios::binary);
    if (!f.is_open()) return 180000; // default 3 min
    char buf[44];
    f.read(buf, 44);
    if (f.gcount() < 44) return 180000;
    if (buf[0]!='R'||buf[1]!='I'||buf[2]!='F'||buf[3]!='F') return 180000;
    DWORD byteRate = *(DWORD*)(buf + 28);
    DWORD dataSize = *(DWORD*)(buf + 40);
    if (byteRate == 0) return 180000;
    return (DWORD)(((double)dataSize / byteRate) * 1000.0);
}

string formatTime(DWORD ms) {
    int s = ms / 1000;
    char buf[16];
    sprintf(buf, "%d:%02d", s/60, s%60);
    return string(buf);
}

DWORD getElapsed() {
    if (g_startTime == 0) return 0;
    return timeGetTime() - g_startTime;
}

// ════════════════════════════════════════════════════════════
//  TICKER
// ════════════════════════════════════════════════════════════
int g_tickerOffset = 0;

string getTicker(const string& name, int width) {
    string padded = name + "   ~   ";
    while ((int)padded.size() < width) padded += padded;
    g_tickerOffset = g_tickerOffset % (int)padded.size();
    string result = "";
    for (int i = 0; i < width; i++)
        result += padded[(g_tickerOffset + i) % padded.size()];
    return result;
}

// ════════════════════════════════════════════════════════════
//  PLAYER STATE
// ════════════════════════════════════════════════════════════
enum Screen { MENU, LIBRARY, NOW_PLAYING, SEARCH, ADD_SONG, DELETE_SONG };

struct Song {
    string filename;
    string name;
};

struct Player {
    vector<Song> songs;
    int    nowPlayingIdx = -1;
    int    cursorIdx     = 0;
    bool   isPlaying     = false;
    bool   isPaused      = false;
    Screen screen        = MENU;
    int    menuCursor    = 0;
};

// ════════════════════════════════════════════════════════════
//  PLAYLIST FILE I/O
// ════════════════════════════════════════════════════════════
void savePlaylist(const Player& p) {
    ofstream f("playlist.txt");
    for (auto& s : p.songs)
        f << s.filename << "|" << s.name << "\n";
}

void loadPlaylist(Player& p) {
    ifstream f("playlist.txt");
    if (!f.is_open()) {
        p.songs.push_back({"Fallen.wav",   "Fallen"});
        p.songs.push_back({"Lifetime.wav", "Lifetime"});
        p.songs.push_back({"Multi.wav",    "Multi"});
        savePlaylist(p);
        return;
    }
    string line;
    while (getline(f, line)) {
        size_t sep = line.find('|');
        if (sep == string::npos) continue;
        p.songs.push_back({line.substr(0, sep), line.substr(sep+1)});
    }
}

// ════════════════════════════════════════════════════════════
//  PLAYBACK
// ════════════════════════════════════════════════════════════
void playSong(Player& p, int idx) {
    if (idx < 0 || idx >= (int)p.songs.size()) return;
    PlaySound(NULL, NULL, 0);
    PlaySound(p.songs[idx].filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
    p.nowPlayingIdx = idx;
    p.isPlaying     = true;
    p.isPaused      = false;
    g_startTime     = timeGetTime();
    g_pausedAt      = 0;
    g_songDuration  = getWavDuration(p.songs[idx].filename);
}

void stopPlayback(Player& p) {
    PlaySound(NULL, NULL, 0);
    p.isPlaying = false;
    p.isPaused  = false;
    g_startTime = 0;
    g_pausedAt  = 0;
}

void togglePause(Player& p) {
    if (!p.isPlaying && !p.isPaused) return;
    if (!p.isPaused) {
        g_pausedAt = getElapsed();
        PlaySound(NULL, NULL, 0);
        p.isPaused  = true;
        p.isPlaying = false;
    } else {
        g_startTime = timeGetTime() - g_pausedAt;
        PlaySound(p.songs[p.nowPlayingIdx].filename.c_str(), NULL, SND_FILENAME | SND_ASYNC);
        p.isPaused  = false;
        p.isPlaying = true;
    }
}

// ════════════════════════════════════════════════════════════
//  PROGRESS BAR
// ════════════════════════════════════════════════════════════
void drawProgressBar(int barWidth) {
    DWORD elapsed  = (g_startTime == 0) ? 0 : getElapsed();
    DWORD duration = (g_songDuration == 0) ? 1 : g_songDuration;
    if (elapsed > duration) elapsed = duration;

    double pct  = (double)elapsed / duration;
    int    fill = (int)(pct * barWidth);

    cout << CY << "[" << R << GN << BOLD;
    for (int i = 0; i < fill; i++)        cout << "\xe2\x96\x88"; // █
    cout << R << DG;
    for (int i = fill; i < barWidth; i++) cout << "\xe2\x96\x91"; // ░
    cout << R << CY << "]" << R;
    cout << "  " << W << formatTime(elapsed) << DG << " / " << LG << formatTime(duration) << R;
}

// ════════════════════════════════════════════════════════════
//  SHARED HEADER
// ════════════════════════════════════════════════════════════
void drawHeader() {
    cout << "\n";
    cout << CY2 << BOLD;
    cout << "  \xe2\x95\x94"; for(int i=0;i<54;i++) cout<<"="; cout << "\xe2\x95\x97\n";
    cout << "  \xe2\x95\x91" << R << W << BOLD
         << centerStr("  >> REAL MUSIC PLAYER <<  ", 54)
         << CY2 << "\xe2\x95\x91\n";
    cout << CY2 << "  \xe2\x95\x91" << R << DG
         << centerStr("Windows Terminal Edition  |  wav", 54)
         << CY2 << "\xe2\x95\x91\n";
    cout << CY2 << "  \xe2\x95\x9a"; for(int i=0;i<54;i++) cout<<"="; cout << "\xe2\x95\x9d\n";
    cout << R << "\n";
}

// ════════════════════════════════════════════════════════════
//  MINI NOW-PLAYING BAR (shown on every screen)
// ════════════════════════════════════════════════════════════
void drawMiniBar(const Player& p) {
    cout << DG << "  "; printLine('-', 54, DG); cout << "\n";
    if (p.nowPlayingIdx < 0) {
        cout << DG << "  [ No song playing ]\n" << R;
    } else {
        string name = p.songs[p.nowPlayingIdx].name;
        cout << "  ";
        if (p.isPlaying)       cout << GN << BOLD << "\xe2\x96\xb6 " << R;
        else if (p.isPaused)   cout << OR << BOLD << "\xe2\x8f\xb8 " << R;
        else                   cout << DG << "\xe2\x96\xa0 " << R;

        cout << CY << BOLD << getTicker(name, 28) << R;
        cout << DG << "  [P] pause/play\n";
        cout << "  ";
        drawProgressBar(28);
        cout << "\n";
    }
    cout << DG << "  "; printLine('-', 54, DG); cout << "\n\n";
}

// ════════════════════════════════════════════════════════════
//  SCREEN: MAIN MENU
// ════════════════════════════════════════════════════════════
const vector<string> MENU_ITEMS = {
    "  Library       —  browse & play songs",
    "  Search        —  find a song live",
    "  Now Playing   —  full player view",
    "  Add Song      —  add a new wav file",
    "  Delete Song   —  remove from library",
    "  Exit"
};

void drawMenu(Player& p) {
    cls(); hideCursor();
    drawHeader();
    drawMiniBar(p);

    cout << W << BOLD << "  MAIN MENU\n" << R;
    cout << DG << "  "; printLine('-', 42, DG); cout << "\n";

    for (int i = 0; i < (int)MENU_ITEMS.size(); i++) {
        if (i == p.menuCursor) {
            cout << BG_SEL << CY << BOLD << " >> " << MENU_ITEMS[i]
                 << string(max(0, 38-(int)MENU_ITEMS[i].size()), ' ') << R << "\n";
        } else {
            cout << LG << "    " << MENU_ITEMS[i] << R << "\n";
        }
    }

    cout << DG << "  "; printLine('-', 42, DG); cout << "\n";
    cout << DG << "  UP/DOWN = navigate   ENTER = select\n" << R;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: LIBRARY
// ════════════════════════════════════════════════════════════
void drawLibrary(Player& p) {
    cls(); hideCursor();
    drawHeader();
    drawMiniBar(p);

    cout << W << BOLD << "  LIBRARY\n" << R;
    cout << DG << "  "; printLine('-', 42, DG); cout << "\n";

    if (p.songs.empty()) {
        cout << DG << "  No songs. Add one from the main menu.\n" << R;
    }

    for (int i = 0; i < (int)p.songs.size(); i++) {
        bool isCursor  = (i == p.cursorIdx);
        bool isPlaying = (i == p.nowPlayingIdx && p.isPlaying);

        cout << "  ";
        if (isCursor && isPlaying) {
            cout << BG_NOW << GN << BOLD
                 << " >> [" << (i+1) << "] " << p.songs[i].name << "  \xe2\x99\xaa"
                 << string(max(0, 26-(int)p.songs[i].name.size()), ' ') << R << "\n";
        } else if (isCursor) {
            cout << BG_SEL << CY << BOLD
                 << " >> [" << (i+1) << "] " << p.songs[i].name
                 << string(max(0, 28-(int)p.songs[i].name.size()), ' ') << R << "\n";
        } else if (isPlaying) {
            cout << GN2 << "    [" << (i+1) << "] " << p.songs[i].name
                 << "  \xe2\x99\xaa" << R << "\n";
        } else {
            cout << LG << "    [" << (i+1) << "] " << p.songs[i].name << R << "\n";
        }
    }

    cout << DG << "  "; printLine('-', 42, DG); cout << "\n";
    cout << DG << "  UP/DOWN = navigate   ENTER = play   ESC = back\n" << R;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: NOW PLAYING
// ════════════════════════════════════════════════════════════
void drawNowPlaying(Player& p) {
    cls(); hideCursor();
    drawHeader();

    if (p.nowPlayingIdx < 0) {
        cout << DG << "  Nothing is playing yet.\n"
             << "  Go to Library or Search and pick a song!\n\n" << R;
        cout << DG << "  ESC = back\n" << R;
        return;
    }

    string name = p.songs[p.nowPlayingIdx].name;
    string file = p.songs[p.nowPlayingIdx].filename;

    cout << "\n  " << DG << "NOW PLAYING\n" << R;
    cout << "  " << CY; printLine('~', 50, CY); cout << "\n";
    cout << "  " << W << BOLD << "  " << name << "\n" << R;
    cout << "  " << DG << "  " << file << "\n" << R;
    cout << "  " << CY; printLine('~', 50, CY); cout << "\n\n";

    cout << "  ";
    if (p.isPlaying)      cout << GN << BOLD << "[ \xe2\x96\xb6 PLAYING ]" << R;
    else if (p.isPaused)  cout << OR << BOLD << "[ \xe2\x8f\xb8 PAUSED  ]" << R;
    else                  cout << DG <<         "[  STOPPED ]" << R;
    cout << "\n\n";

    cout << "  "; drawProgressBar(44); cout << "\n\n";
    cout << "  " << PK << getTicker(name, 44) << R << "\n\n";

    cout << DG << "  "; printLine('-', 44, DG); cout << "\n";
    cout << DG << "  [P] Play/Pause    [S] Stop    [ESC] Back\n" << R;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: LIVE SEARCH
// ════════════════════════════════════════════════════════════
// Two modes:
//   TYPING  — keypresses go into the search query string
//   RESULTS — arrow keys move through filtered results
//
// Switching modes:
//   DOWN arrow while in TYPING  → jump into results
//   UP arrow  while on result 0 → jump back to search bar
//   Any letter/backspace        → always goes back to TYPING mode

void drawSearch(const Player& p,
                const string& query,
                const vector<int>& results,
                int resultCursor,
                bool inResults)
{
    cls(); hideCursor();
    drawHeader();
    drawMiniBar(p);

    cout << W << BOLD << "  SEARCH\n" << R;
    cout << DG << "  "; printLine('-', 44, DG); cout << "\n\n";

    // Search bar
    // Highlight the bar differently depending on focus
    if (!inResults) {
        // Typing mode — bar is active/highlighted
        cout << "  " << BG_SRCH << CY << BOLD
             << "  / " << query << "_"
             << string(max(0, 36-(int)query.size()), ' ')
             << R << "\n\n";
    } else {
        // Results mode — bar is dimmed
        cout << "  " << DG
             << "  / " << query
             << string(max(0, 37-(int)query.size()), ' ')
             << R << "\n\n";
    }

    // Results list
    if (query.empty()) {
        cout << DG << "  Type to search...\n" << R;
    } else if (results.empty()) {
        cout << RD << "  No songs found for \"" << query << "\"\n" << R;
    } else {
        cout << MG << "  Results (" << results.size() << " found):\n" << R;
        cout << DG << "  "; printLine('-', 40, DG); cout << "\n";

        for (int i = 0; i < (int)results.size(); i++) {
            int songIdx    = results[i];
            bool isCursor  = inResults && (i == resultCursor);
            bool isPlaying = (songIdx == p.nowPlayingIdx && p.isPlaying);

            cout << "  ";
            if (isCursor && isPlaying) {
                cout << BG_NOW << GN << BOLD
                     << " >> " << p.songs[songIdx].name << "  \xe2\x99\xaa"
                     << string(max(0, 34-(int)p.songs[songIdx].name.size()), ' ')
                     << R << "\n";
            } else if (isCursor) {
                cout << BG_SEL << CY2 << BOLD
                     << " >> " << p.songs[songIdx].name
                     << string(max(0, 36-(int)p.songs[songIdx].name.size()), ' ')
                     << R << "\n";
            } else if (isPlaying) {
                cout << GN2 << "    " << p.songs[songIdx].name
                     << "  \xe2\x99\xaa" << R << "\n";
            } else {
                // Highlight the matching part of the name
                string sname = p.songs[songIdx].name;
                string slow  = sname;
                string qlow  = query;
                transform(slow.begin(), slow.end(), slow.begin(), ::tolower);
                transform(qlow.begin(), qlow.end(), qlow.begin(), ::tolower);

                size_t pos = slow.find(qlow);
                if (pos != string::npos) {
                    // Print: normal + highlighted match + normal
                    cout << LG << "    "
                         << sname.substr(0, pos)
                         << YL << BOLD << sname.substr(pos, query.size()) << R
                         << LG << sname.substr(pos + query.size())
                         << R << "\n";
                } else {
                    cout << LG << "    " << sname << R << "\n";
                }
            }
        }
        cout << DG << "  "; printLine('-', 40, DG); cout << "\n";
    }

    // Controls hint
    cout << "\n";
    if (!inResults) {
        cout << DG << "  Type to filter   DOWN = go to results   ESC = back\n" << R;
    } else {
        cout << DG << "  UP/DOWN = navigate   ENTER = play   Type = search again   ESC = back\n" << R;
    }
}

// Search screen input loop (self-contained)
void screenSearch(Player& p) {
    string query      = "";
    int    resultCursor = 0;
    bool   inResults  = false;

    while (true) {
        // Build filtered results
        vector<int> results;
        for (int i = 0; i < (int)p.songs.size(); i++) {
            if (containsCI(p.songs[i].name, query))
                results.push_back(i);
        }

        // Clamp cursor
        if (resultCursor >= (int)results.size())
            resultCursor = max(0, (int)results.size()-1);

        // Advance ticker
        if (p.isPlaying) g_tickerOffset++;

        drawSearch(p, query, results, resultCursor, inResults);

        int key = _getch();

        // Arrow keys come as 224 + scancode
        if (key == 224) {
            int k2 = _getch();

            if (k2 == 72) {
                // UP arrow
                if (inResults) {
                    if (resultCursor > 0) {
                        resultCursor--;
                    } else {
                        // At top of results — go back to search bar
                        inResults = false;
                    }
                }
                // If already in typing mode, UP does nothing
            } else if (k2 == 80) {
                // DOWN arrow
                if (!inResults && !results.empty()) {
                    // Jump from search bar into results
                    inResults    = true;
                    resultCursor = 0;
                } else if (inResults) {
                    resultCursor++;
                    if (resultCursor >= (int)results.size())
                        resultCursor = (int)results.size()-1;
                }
            }

        } else if (key == 27) {
            // ESC — back to menu
            p.screen = MENU;
            return;

        } else if (key == 13) {
            // ENTER
            if (inResults && !results.empty()) {
                playSong(p, results[resultCursor]);
                p.screen = NOW_PLAYING;
                return;
            }

        } else if (key == 8) {
            // BACKSPACE — delete last char, go back to typing mode
            if (!query.empty()) query.pop_back();
            inResults    = false;
            resultCursor = 0;

        } else if (key == 'p' || key == 'P') {
            // P = pause/play (works in search too)
            togglePause(p);

        } else if (key >= 32 && key <= 126) {
            // Printable character — add to query, switch to typing mode
            query      += (char)key;
            inResults   = false;
            resultCursor = 0;
        }
    }
}

// ════════════════════════════════════════════════════════════
//  SCREEN: ADD SONG
// ════════════════════════════════════════════════════════════
void screenAddSong(Player& p) {
    cls(); showCursor();
    drawHeader();

    cout << W << BOLD << "  ADD SONG\n" << R;
    cout << DG << "  "; printLine('-', 40, DG); cout << "\n\n";
    cout << LG << "  .wav file must be in the SAME folder as music.exe\n\n" << R;

    cout << W << "  Filename (e.g. Multo.wav): " << CY;
    string filename; getline(cin, filename);

    cout << R << W << "  Display name (e.g. Multo): " << CY;
    string displayName; getline(cin, displayName);
    cout << R;

    if (filename.empty() || displayName.empty()) {
        cout << RD << "\n  Cancelled.\n" << R;
        Sleep(1000); p.screen = MENU; return;
    }

    ifstream test(filename);
    if (!test.good()) {
        cout << RD << "\n  Warning: \"" << filename << "\" not found.\n";
        cout << OR << "  Add anyway? (y/n): " << R;
        char c; cin >> c; cin.ignore();
        if (tolower(c) != 'y') { p.screen = MENU; return; }
    }

    p.songs.push_back({filename, displayName});
    savePlaylist(p);

    cout << GN << "\n  Added: " << displayName << "\n" << R;
    Sleep(1200);
    p.screen    = LIBRARY;
    p.cursorIdx = (int)p.songs.size()-1;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: DELETE SONG
// ════════════════════════════════════════════════════════════
void drawDeleteSong(Player& p) {
    cls(); hideCursor();
    drawHeader();

    cout << W << BOLD << "  DELETE SONG\n" << R;
    cout << DG << "  "; printLine('-', 40, DG); cout << "\n";

    if (p.songs.empty()) {
        cout << DG << "  No songs to delete.\n" << R;
        cout << DG << "\n  ESC = back\n" << R;
        return;
    }

    for (int i = 0; i < (int)p.songs.size(); i++) {
        bool isCursor = (i == p.cursorIdx);
        cout << "  ";
        if (isCursor) {
            cout << BG_SEL << RD << BOLD
                 << " >> [" << (i+1) << "] " << p.songs[i].name
                 << string(max(0, 30-(int)p.songs[i].name.size()), ' ')
                 << R << "\n";
        } else {
            cout << LG << "    [" << (i+1) << "] " << p.songs[i].name << R << "\n";
        }
    }

    cout << DG << "  "; printLine('-', 40, DG); cout << "\n";
    cout << DG << "  UP/DOWN = select   ENTER = delete   ESC = back\n" << R;
}

// ════════════════════════════════════════════════════════════
//  KEY READING
// ════════════════════════════════════════════════════════════
int readKey() {
    int k = _getch();
    if (k == 224) return 1000 + _getch();
    return k;
}
const int KEY_UP    = 1072;
const int KEY_DOWN  = 1080;
const int KEY_ENTER = 13;
const int KEY_ESC   = 27;

// ════════════════════════════════════════════════════════════
//  MAIN
// ════════════════════════════════════════════════════════════
int main() {
    initConsole();
    hideCursor();

    Player p;
    loadPlaylist(p);
    p.screen     = MENU;
    p.menuCursor = 0;
    p.cursorIdx  = 0;

    while (true) {

        if (p.isPlaying) g_tickerOffset++;

        // Search has its own input loop
        if (p.screen == SEARCH) {
            screenSearch(p);
            continue;
        }
        if (p.screen == ADD_SONG) {
            screenAddSong(p);
            continue;
        }

        // Draw current screen
        switch (p.screen) {
            case MENU:         drawMenu(p);        break;
            case LIBRARY:      drawLibrary(p);     break;
            case NOW_PLAYING:  drawNowPlaying(p);  break;
            case DELETE_SONG:  drawDeleteSong(p);  break;
            default: break;
        }

        int key = readKey();

        // Global: P = pause/play
        if (toupper(key) == 'P') { togglePause(p); continue; }
        // Global: S = stop
        if (toupper(key) == 'S') { stopPlayback(p); continue; }

        switch (p.screen) {

            case MENU:
                if (key == KEY_UP) {
                    p.menuCursor--;
                    if (p.menuCursor < 0) p.menuCursor = (int)MENU_ITEMS.size()-1;
                } else if (key == KEY_DOWN) {
                    p.menuCursor++;
                    if (p.menuCursor >= (int)MENU_ITEMS.size()) p.menuCursor = 0;
                } else if (key == KEY_ENTER) {
                    switch (p.menuCursor) {
                        case 0: p.screen = LIBRARY;     p.cursorIdx = 0; break;
                        case 1: p.screen = SEARCH;      break;
                        case 2: p.screen = NOW_PLAYING; break;
                        case 3: p.screen = ADD_SONG;    break;
                        case 4: p.screen = DELETE_SONG; p.cursorIdx = 0; break;
                        case 5:
                            stopPlayback(p);
                            showCursor(); cls();
                            cout << CY << BOLD << "\n  Thanks for listening!\n\n" << R;
                            return 0;
                    }
                }
                break;

            case LIBRARY:
                if (key == KEY_UP) {
                    p.cursorIdx--;
                    if (p.cursorIdx < 0) p.cursorIdx = (int)p.songs.size()-1;
                } else if (key == KEY_DOWN) {
                    p.cursorIdx++;
                    if (p.cursorIdx >= (int)p.songs.size()) p.cursorIdx = 0;
                } else if (key == KEY_ENTER) {
                    playSong(p, p.cursorIdx);
                } else if (key == KEY_ESC) {
                    p.screen = MENU;
                }
                break;

            case NOW_PLAYING:
                if (key == KEY_ESC) p.screen = MENU;
                break;

            case DELETE_SONG:
                if (key == KEY_UP) {
                    p.cursorIdx--;
                    if (p.cursorIdx < 0) p.cursorIdx = (int)p.songs.size()-1;
                } else if (key == KEY_DOWN) {
                    p.cursorIdx++;
                    if (p.cursorIdx >= (int)p.songs.size()) p.cursorIdx = 0;
                } else if (key == KEY_ENTER && !p.songs.empty()) {
                    if (p.cursorIdx == p.nowPlayingIdx) {
                        stopPlayback(p); p.nowPlayingIdx = -1;
                    } else if (p.cursorIdx < p.nowPlayingIdx) {
                        p.nowPlayingIdx--;
                    }
                    p.songs.erase(p.songs.begin() + p.cursorIdx);
                    savePlaylist(p);
                    if (p.cursorIdx >= (int)p.songs.size())
                        p.cursorIdx = max(0, (int)p.songs.size()-1);
                } else if (key == KEY_ESC) {
                    p.screen = MENU;
                }
                break;

            default: break;
        }
    }

    return 0;
}
