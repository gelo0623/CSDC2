// ============================================================
// realMusicPlayer.cpp
// Terminal Music Player — Full Featured
// Windows only (conio.h + winmm)
//
// Compile:  g++ realMusicPlayer.cpp -o music -lwinmm
// Run:      music.exe
//
// FEATURES:
//   - Main Menu, Now Playing screen, Library screen
//   - Animated progress bar + song timer
//   - Arrow key navigation + Enter to select
//   - Play / Pause toggle
//   - Song keeps playing when you go back to menu
//   - Add song / Delete song from library
//   - Animated now-playing ticker
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// ════════════════════════════════════════════════════════════
//  ANSI COLORS & STYLES
// ════════════════════════════════════════════════════════════
#define R       "\033[0m"
#define BOLD    "\033[1m"
#define DIM     "\033[2m"

// Foreground colors
#define CY      "\033[38;5;51m"     // bright cyan
#define CY2     "\033[38;5;87m"     // lighter cyan
#define YL      "\033[38;5;220m"    // yellow
#define GN      "\033[38;5;82m"     // green
#define GN2     "\033[38;5;48m"     // mint green
#define OR      "\033[38;5;208m"    // orange
#define PK      "\033[38;5;213m"    // pink
#define RD      "\033[38;5;203m"    // red
#define W       "\033[38;5;255m"    // white
#define LG      "\033[38;5;250m"    // light gray
#define DG      "\033[38;5;240m"    // dark gray
#define MG      "\033[38;5;245m"    // mid gray
#define BL      "\033[38;5;117m"    // blue

// Background
#define BG_SEL  "\033[48;5;234m"    // very dark bg for selected row
#define BG_NOW  "\033[48;5;22m"     // dark green bg for now playing row

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
    // Set window title
    SetConsoleTitleA("RealMusicPlayer");
}

void cls()        { system("cls"); }
void hideCursor() { cout << "\033[?25l"; }
void showCursor() { cout << "\033[?25h"; }

void gotoxy(int row, int col) {
    cout << "\033[" << row << ";" << col << "H";
}

// Print a line of repeated chars
void printLine(char c, int n, const char* color = DG) {
    cout << color;
    for (int i = 0; i < n; i++) cout << c;
    cout << R;
}

// Center a string inside a width
string center(const string& s, int width) {
    int pad = (width - (int)s.size()) / 2;
    if (pad < 0) pad = 0;
    return string(pad, ' ') + s;
}

// ════════════════════════════════════════════════════════════
//  SONG DURATION TRACKING (using timeGetTime)
// ════════════════════════════════════════════════════════════
// winmm can't query playback position for wav files natively,
// so we track elapsed time ourselves using system clock.
// We estimate song length by reading the wav header.

DWORD g_startTime    = 0;   // when current song started (ms)
DWORD g_pausedAt     = 0;   // elapsed ms when paused
DWORD g_songDuration = 0;   // estimated duration in ms (from wav header)

// Read the duration of a WAV file by parsing its header
// Returns duration in milliseconds, or 60000 (1 min) if unreadable
DWORD getWavDuration(const string& filename) {
    ifstream f(filename, ios::binary);
    if (!f.is_open()) return 60000;

    // WAV header structure:
    // Offset 24: sample rate (4 bytes)
    // Offset 28: byte rate   (4 bytes)
    // Offset 40: data chunk size (4 bytes)  — bytes of audio data
    // duration_ms = (dataSize / byteRate) * 1000

    char buf[44];
    f.read(buf, 44);
    if (f.gcount() < 44) return 60000;

    // Check RIFF header
    if (buf[0]!='R'||buf[1]!='I'||buf[2]!='F'||buf[3]!='F') return 60000;

    DWORD byteRate  = *(DWORD*)(buf + 28);
    DWORD dataSize  = *(DWORD*)(buf + 40);

    if (byteRate == 0) return 60000;

    DWORD durationMs = (DWORD)(((double)dataSize / byteRate) * 1000.0);
    return durationMs;
}

// Format ms as "M:SS"
string formatTime(DWORD ms) {
    int totalSec = ms / 1000;
    int m = totalSec / 60;
    int s = totalSec % 60;
    char buf[16];
    sprintf(buf, "%d:%02d", m, s);
    return string(buf);
}

// Get elapsed playback time in ms
DWORD getElapsed() {
    if (g_startTime == 0) return 0;
    return timeGetTime() - g_startTime;
}

// ════════════════════════════════════════════════════════════
//  PLAYER STATE
// ════════════════════════════════════════════════════════════
enum Screen { MENU, LIBRARY, NOW_PLAYING, ADD_SONG, DELETE_SONG };

struct Song {
    string filename;    // e.g. "Fallen.wav"
    string name;        // e.g. "Fallen"
};

struct Player {
    vector<Song> songs;
    int  nowPlayingIdx = -1;   // which song is playing (-1 = none)
    int  cursorIdx     = 0;    // arrow key cursor position
    bool isPlaying     = false;
    bool isPaused      = false;
    Screen screen      = MENU;
    int  menuCursor    = 0;    // cursor for main menu items
};

// ════════════════════════════════════════════════════════════
//  SAVE / LOAD PLAYLIST from playlist.txt
// ════════════════════════════════════════════════════════════
// Each line: filename|displayname
// Example:   Fallen.wav|Fallen

void savePlaylist(const Player& p) {
    ofstream f("playlist.txt");
    for (auto& s : p.songs) {
        f << s.filename << "|" << s.name << "\n";
    }
}

void loadPlaylist(Player& p) {
    ifstream f("playlist.txt");
    if (!f.is_open()) {
        // First run defaults
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
        Song s;
        s.filename = line.substr(0, sep);
        s.name     = line.substr(sep + 1);
        p.songs.push_back(s);
    }
}

// ════════════════════════════════════════════════════════════
//  PLAYBACK CONTROLS
// ════════════════════════════════════════════════════════════
void playSong(Player& p, int idx) {
    if (idx < 0 || idx >= (int)p.songs.size()) return;

    PlaySound(NULL, NULL, 0);
    PlaySound(p.songs[idx].filename.c_str(), NULL,
              SND_FILENAME | SND_ASYNC);

    p.nowPlayingIdx = idx;
    p.isPlaying     = true;
    p.isPaused      = false;

    g_startTime    = timeGetTime();
    g_pausedAt     = 0;
    g_songDuration = getWavDuration(p.songs[idx].filename);
}

void stopPlayback(Player& p) {
    PlaySound(NULL, NULL, 0);
    p.isPlaying     = false;
    p.isPaused      = false;
    g_startTime     = 0;
    g_pausedAt      = 0;
}

void togglePause(Player& p) {
    if (!p.isPlaying && !p.isPaused) return;

    if (!p.isPaused) {
        // Pause
        g_pausedAt = getElapsed();  // save how far we got
        PlaySound(NULL, NULL, 0);
        p.isPaused  = true;
        p.isPlaying = false;
    } else {
        // Resume — restart from beginning (winmm limitation)
        // We keep g_startTime offset so timer looks continuous
        g_startTime = timeGetTime() - g_pausedAt;
        PlaySound(p.songs[p.nowPlayingIdx].filename.c_str(), NULL,
                  SND_FILENAME | SND_ASYNC);
        p.isPaused  = false;
        p.isPlaying = true;
    }
}

// ════════════════════════════════════════════════════════════
//  PROGRESS BAR
// ════════════════════════════════════════════════════════════
// Draws: [████████████░░░░░░░░]  1:23 / 3:45
void drawProgressBar(int barWidth) {
    DWORD elapsed  = (g_startTime == 0) ? 0 : getElapsed();
    DWORD duration = (g_songDuration == 0) ? 1 : g_songDuration;

    if (elapsed > duration) elapsed = duration;

    double pct  = (double)elapsed / duration;
    int    fill = (int)(pct * barWidth);

    cout << CY << "[" << R;
    cout << GN << BOLD;
    for (int i = 0; i < fill; i++)       cout << "\xe2\x96\x88"; // █
    cout << R << DG;
    for (int i = fill; i < barWidth; i++) cout << "\xe2\x96\x91"; // ░
    cout << R << CY << "]" << R;

    cout << "  " << W << formatTime(elapsed)
         << DG << " / "
         << LG << formatTime(duration) << R;
}

// ════════════════════════════════════════════════════════════
//  ANIMATED TICKER (scrolling song name)
// ════════════════════════════════════════════════════════════
// Returns a 30-char window of the scrolling title
int g_tickerOffset = 0;
string getTicker(const string& name, int width) {
    string padded = name + "   ~   ";  // gap between repeats
    while ((int)padded.size() < width) padded += padded;

    g_tickerOffset = g_tickerOffset % (int)padded.size();
    string result = "";
    for (int i = 0; i < width; i++) {
        result += padded[(g_tickerOffset + i) % padded.size()];
    }
    return result;
}

// ════════════════════════════════════════════════════════════
//  DRAW: HEADER BANNER
// ════════════════════════════════════════════════════════════
void drawHeader() {
    cout << "\n";
    cout << CY2 << BOLD;
    cout << "  \xe2\x95\x94"; printLine('=', 54, CY2); cout << CY2 << "\xe2\x95\x97\n";
    cout << "  \xe2\x95\x91" << R << W << BOLD
         << center("  >> REAL MUSIC PLAYER <<  ", 54)
         << CY2 << "\xe2\x95\x91\n";
    cout << CY2 << "  \xe2\x95\x91" << R << DG
         << center("Windows Terminal Edition  |  wav", 54)
         << CY2 << "\xe2\x95\x91\n";
    cout << CY2 << "  \xe2\x95\x9a"; printLine('=', 54, CY2); cout << CY2 << "\xe2\x95\x9d\n";
    cout << R << "\n";
}

// ════════════════════════════════════════════════════════════
//  DRAW: MINI NOW-PLAYING BAR (shown on every screen)
// ════════════════════════════════════════════════════════════
void drawMiniBar(const Player& p) {
    cout << DG << "  "; printLine('-', 54, DG); cout << "\n";

    if (p.nowPlayingIdx < 0) {
        cout << DG << "  [ No song playing ]\n";
    } else {
        string name = p.songs[p.nowPlayingIdx].name;

        // Status icon
        cout << "  ";
        if (p.isPlaying)
            cout << GN << BOLD << "\xe2\x96\xb6 " << R;   // ▶
        else if (p.isPaused)
            cout << OR << BOLD << "\xe2\x8f\xb8 " << R;   // ⏸
        else
            cout << DG << "\xe2\x96\xa0 " << R;            // ■

        // Scrolling ticker
        cout << CY << BOLD << getTicker(name, 30) << R;

        // Pause hint
        cout << DG << "  [P] pause/play\n";

        // Progress bar
        cout << "  ";
        drawProgressBar(30);
        cout << "\n";
    }

    cout << DG << "  "; printLine('-', 54, DG); cout << "\n\n";
}

// ════════════════════════════════════════════════════════════
//  SCREEN: MAIN MENU
// ════════════════════════════════════════════════════════════
const vector<string> MENU_ITEMS = {
    "  Library  —  browse & play songs",
    "  Now Playing  —  full player view",
    "  Add Song  —  add a new wav file",
    "  Delete Song  —  remove from library",
    "  Exit"
};

void drawMenu(Player& p) {
    cls();
    hideCursor();
    drawHeader();
    drawMiniBar(p);

    cout << W << BOLD << "  MAIN MENU\n" << R;
    cout << DG << "  "; printLine('-', 40, DG); cout << "\n";

    for (int i = 0; i < (int)MENU_ITEMS.size(); i++) {
        if (i == p.menuCursor) {
            cout << BG_SEL << CY << BOLD << " >> " << MENU_ITEMS[i]
                 << string(max(0, 36 - (int)MENU_ITEMS[i].size()), ' ')
                 << R << "\n";
        } else {
            cout << LG << "    " << MENU_ITEMS[i] << R << "\n";
        }
    }

    cout << DG << "  "; printLine('-', 40, DG); cout << "\n";
    cout << DG << "  UP/DOWN = navigate   ENTER = select\n" << R;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: LIBRARY
// ════════════════════════════════════════════════════════════
void drawLibrary(Player& p) {
    cls();
    hideCursor();
    drawHeader();
    drawMiniBar(p);

    cout << W << BOLD << "  LIBRARY\n" << R;
    cout << DG << "  "; printLine('-', 40, DG); cout << "\n";

    if (p.songs.empty()) {
        cout << DG << "  No songs. Add one from the main menu.\n" << R;
    }

    for (int i = 0; i < (int)p.songs.size(); i++) {
        bool isCursor   = (i == p.cursorIdx);
        bool isPlaying  = (i == p.nowPlayingIdx);

        cout << "  ";

        if (isCursor && isPlaying) {
            cout << BG_NOW << GN << BOLD
                 << " >> [" << (i+1) << "] " << p.songs[i].name
                 << "  \xe2\x99\xaa"   // ♪
                 << string(max(0, 28-(int)p.songs[i].name.size()), ' ')
                 << R << "\n";
        } else if (isCursor) {
            cout << BG_SEL << CY << BOLD
                 << " >> [" << (i+1) << "] " << p.songs[i].name
                 << string(max(0, 30-(int)p.songs[i].name.size()), ' ')
                 << R << "\n";
        } else if (isPlaying) {
            cout << GN2
                 << "    [" << (i+1) << "] " << p.songs[i].name
                 << "  \xe2\x99\xaa" << R << "\n";
        } else {
            cout << LG
                 << "    [" << (i+1) << "] " << p.songs[i].name
                 << R << "\n";
        }
    }

    cout << DG << "  "; printLine('-', 40, DG); cout << "\n";
    cout << DG << "  UP/DOWN = navigate   ENTER = play   ESC = back\n" << R;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: NOW PLAYING (full view)
// ════════════════════════════════════════════════════════════
void drawNowPlaying(Player& p) {
    cls();
    hideCursor();
    drawHeader();

    if (p.nowPlayingIdx < 0) {
        cout << DG << "  Nothing is playing yet.\n"
             << "  Go to Library and pick a song!\n\n" << R;
        cout << DG << "  ESC = back to menu\n" << R;
        return;
    }

    string name = p.songs[p.nowPlayingIdx].name;
    string file = p.songs[p.nowPlayingIdx].filename;

    // Big song name display
    cout << "\n";
    cout << "  " << DG << "NOW PLAYING\n" << R;
    cout << "  " << CY << BOLD;
    printLine('~', 50, CY);
    cout << "\n";
    cout << "  " << W << BOLD << "  " << name << "\n" << R;
    cout << "  " << DG << "  " << file << "\n" << R;
    cout << "  " << CY;
    printLine('~', 50, CY);
    cout << "\n\n";

    // Status
    cout << "  ";
    if (p.isPlaying)
        cout << GN << BOLD << "[ \xe2\x96\xb6 PLAYING ]" << R;
    else if (p.isPaused)
        cout << OR << BOLD << "[ \xe2\x8f\xb8 PAUSED  ]" << R;
    else
        cout << DG <<         "[  STOPPED ]" << R;
    cout << "\n\n";

    // Full progress bar
    cout << "  ";
    drawProgressBar(44);
    cout << "\n\n";

    // Scrolling ticker
    cout << "  " << PK << getTicker(name, 44) << R << "\n\n";

    // Controls
    cout << DG << "  "; printLine('-', 44, DG); cout << "\n";
    cout << DG << "  [P] Play/Pause    [S] Stop    [ESC] Back to menu\n" << R;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: ADD SONG
// ════════════════════════════════════════════════════════════
void screenAddSong(Player& p) {
    cls();
    showCursor();
    drawHeader();

    cout << W << BOLD << "  ADD SONG\n" << R;
    cout << DG << "  "; printLine('-', 40, DG); cout << "\n\n";
    cout << LG << "  The .wav file must be in the SAME folder as music.exe\n\n" << R;

    cout << W << "  Filename (e.g. mysong.wav): " << CY;
    string filename;
    getline(cin, filename);

    cout << R << W << "  Display name (e.g. My Song): " << CY;
    string displayName;
    getline(cin, displayName);
    cout << R;

    if (filename.empty() || displayName.empty()) {
        cout << RD << "\n  Cancelled — empty input.\n" << R;
        Sleep(1200);
        p.screen = MENU;
        return;
    }

    // Check if file exists
    ifstream test(filename);
    if (!test.good()) {
        cout << RD << "\n  Warning: \"" << filename << "\" not found in this folder.\n";
        cout << OR << "  Add it anyway? (y/n): " << R;
        char c;
        cin >> c;
        cin.ignore();
        if (tolower(c) != 'y') {
            p.screen = MENU;
            return;
        }
    }

    Song s;
    s.filename = filename;
    s.name     = displayName;
    p.songs.push_back(s);
    savePlaylist(p);

    cout << GN << "\n  Added: " << displayName << " (" << filename << ")\n" << R;
    Sleep(1200);
    p.screen = LIBRARY;
    p.cursorIdx = (int)p.songs.size() - 1;
}

// ════════════════════════════════════════════════════════════
//  SCREEN: DELETE SONG
// ════════════════════════════════════════════════════════════
void drawDeleteSong(Player& p) {
    cls();
    hideCursor();
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
//  INPUT HANDLER
// ════════════════════════════════════════════════════════════
// Returns: key code. Arrow keys return 1000+scancode.
int readKey() {
    int k = _getch();
    if (k == 224) {
        int k2 = _getch();
        return 1000 + k2;  // 1072 = UP, 1080 = DOWN
    }
    return k;
}

const int KEY_UP    = 1072;
const int KEY_DOWN  = 1080;
const int KEY_ENTER = 13;
const int KEY_ESC   = 27;

// ════════════════════════════════════════════════════════════
//  TICKER ADVANCE (called every redraw)
// ════════════════════════════════════════════════════════════
void advanceTicker(const Player& p) {
    if (p.isPlaying) {
        g_tickerOffset++;
    }
}

// ════════════════════════════════════════════════════════════
//  MAIN LOOP
// ════════════════════════════════════════════════════════════
int main() {
    initConsole();
    hideCursor();

    Player p;
    loadPlaylist(p);

    p.screen    = MENU;
    p.menuCursor = 0;
    p.cursorIdx  = 0;

    while (true) {

        // ── Draw current screen ──────────────────────────
        advanceTicker(p);

        switch (p.screen) {
            case MENU:         drawMenu(p);       break;
            case LIBRARY:      drawLibrary(p);    break;
            case NOW_PLAYING:  drawNowPlaying(p); break;
            case DELETE_SONG:  drawDeleteSong(p); break;
            case ADD_SONG:
                screenAddSong(p);  // handles its own input loop
                continue;
        }

        // ── Read key ─────────────────────────────────────
        int key = readKey();

        // ── Global: P = pause/play anywhere ──────────────
        if (toupper(key) == 'P') {
            togglePause(p);
            continue;
        }

        // ── Global: S = stop anywhere ────────────────────
        if (toupper(key) == 'S') {
            stopPlayback(p);
            continue;
        }

        // ── Screen-specific input ─────────────────────────
        switch (p.screen) {

            // ── MAIN MENU ──────────────────────────────────
            case MENU:
                if (key == KEY_UP) {
                    p.menuCursor--;
                    if (p.menuCursor < 0) p.
