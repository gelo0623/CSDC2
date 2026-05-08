// ============================================================
// realMusicPlayer.cpp
// A full terminal-based music player using Windows winmm API
// Supports: Play, Pause, Stop, Next, Prev, Loop, Shuffle, Playlist
//
// Compile: g++ realMusicPlayer.cpp -o music -lwinmm
// Run:     music.exe
//
// All .wav files must be in the SAME FOLDER as music.exe
// ============================================================

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  // for shuffle
#include <random>     // for random_device
#include <ctime>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// ─── ANSI COLORS ────────────────────────────────────────────
const string RESET   = "\033[0m";
const string BOLD    = "\033[1m";
const string FG_CYAN    = "\033[38;5;87m";
const string FG_YELLOW  = "\033[38;5;220m";
const string FG_GREEN   = "\033[38;5;82m";
const string FG_RED     = "\033[38;5;203m";
const string FG_PINK    = "\033[38;5;213m";
const string FG_LGRAY   = "\033[38;5;250m";
const string FG_DGRAY   = "\033[38;5;240m";
const string FG_WHITE   = "\033[38;5;255m";
const string FG_ORANGE  = "\033[38;5;208m";

// ─── CONSOLE SETUP ──────────────────────────────────────────
// Enables ANSI color codes on Windows terminal
void initConsole() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hOut, &mode);
    SetConsoleMode(hOut, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
}

void clearScreen() { system("cls"); }

// ─── PLAYER STATE ───────────────────────────────────────────
// This struct holds everything about the current player state.
// Think of it as the "brain" of the music player.

struct MusicPlayer {
    vector<string> playlist;      // list of song filenames (e.g. "song1.wav")
    vector<string> songNames;     // display names (e.g. "Song One")
    vector<int>    playOrder;     // order to play songs (used for shuffle)

    int  currentIndex = 0;        // which song is currently selected
    bool isPlaying    = false;    // is a song currently playing?
    bool isPaused     = false;    // is the song paused?
    bool loopCurrent  = false;    // loop the current song?
    bool shuffleOn    = false;    // shuffle mode on/off?
    bool loopPlaylist = false;    // loop the whole playlist?
};

// ─── PLAYLIST SETUP ─────────────────────────────────────────
// Add your own songs here!
// Format: player.playlist.push_back("filename.wav");
//         player.songNames.push_back("Display Name");
//
// The .wav file must be in the SAME FOLDER as music.exe

void loadPlaylist(MusicPlayer& player) {
    // ── ADD YOUR SONGS HERE ──────────────────────────────────
    player.playlist.push_back("song1.wav");
    player.songNames.push_back("Song One");

    player.playlist.push_back("song2.wav");
    player.songNames.push_back("Song Two");

    player.playlist.push_back("song3.wav");
    player.songNames.push_back("Song Three");

    player.playlist.push_back("song4.wav");
    player.songNames.push_back("Song Four");

    player.playlist.push_back("song5.wav");
    player.songNames.push_back("Song Five");
    // ── END OF SONG LIST ────────────────────────────────────

    // Build default play order (0, 1, 2, 3, ...)
    for (int i = 0; i < (int)player.playlist.size(); i++) {
        player.playOrder.push_back(i);
    }
}

// ─── SHUFFLE ────────────────────────────────────────────────
// Randomizes the playOrder vector so songs play in random order.
// The current song stays at position 0 so it keeps playing.

void shufflePlaylist(MusicPlayer& player) {
    // Use a proper random engine (better than rand())
    random_device rd;
    mt19937 g(rd());

    shuffle(player.playOrder.begin(), player.playOrder.end(), g);

    // Make sure the current song is still first after shuffle
    // Find where currentIndex ended up and swap it to front
    for (int i = 0; i < (int)player.playOrder.size(); i++) {
        if (player.playOrder[i] == player.currentIndex) {
            swap(player.playOrder[0], player.playOrder[i]);
            break;
        }
    }

    player.currentIndex = 0; // reset position to front of new order
}

// ─── PLAY SONG ──────────────────────────────────────────────
// Plays the song at the current index using PlaySound().
// SND_ASYNC = plays in background so program keeps running
// SND_LOOP  = loops the current track (only if loopCurrent is on)

void playSong(MusicPlayer& player) {
    if (player.playlist.empty()) return;

    // Get the actual song index from playOrder
    int actualIndex = player.playOrder[player.currentIndex];
    string filename = player.playlist[actualIndex];

    // Stop any currently playing sound first
    PlaySound(NULL, NULL, 0);

    // Play the new song
    DWORD flags = SND_FILENAME | SND_ASYNC;
    if (player.loopCurrent) {
        flags |= SND_LOOP;  // loop this one song
    }

    PlaySound(filename.c_str(), NULL, flags);

    player.isPlaying = true;
    player.isPaused  = false;
}

// ─── STOP SONG ──────────────────────────────────────────────
void stopSong(MusicPlayer& player) {
    PlaySound(NULL, NULL, 0);  // passing NULL stops playback
    player.isPlaying = false;
    player.isPaused  = false;
}

// ─── PAUSE / RESUME ─────────────────────────────────────────
// winmm's PlaySound doesn't natively support pause/resume.
// We simulate it by stopping and remembering the paused state.
// (True pause with position tracking requires MCI — this is the
//  simpler winmm approach used in beginner C++ projects.)

void togglePause(MusicPlayer& player) {
    if (!player.isPlaying) return;

    if (!player.isPaused) {
        // Pause: stop sound but remember we're paused
        PlaySound(NULL, NULL, 0);
        player.isPaused = true;
        player.isPlaying = false;
    } else {
        // Resume: play again from start (winmm limitation)
        playSong(player);
        player.isPaused = false;
    }
}

// ─── NEXT SONG ──────────────────────────────────────────────
void nextSong(MusicPlayer& player) {
    if (player.playlist.empty()) return;

    player.currentIndex++;

    // If we've gone past the last song
    if (player.currentIndex >= (int)player.playlist.size()) {
        if (player.loopPlaylist) {
            player.currentIndex = 0;  // go back to start
        } else {
            player.currentIndex = (int)player.playlist.size() - 1;
            stopSong(player);
            cout << FG_DGRAY << "  End of playlist.\n" << RESET;
            return;
        }
    }

    playSong(player);
}

// ─── PREVIOUS SONG ──────────────────────────────────────────
void prevSong(MusicPlayer& player) {
    if (player.playlist.empty()) return;

    player.currentIndex--;

    // If we've gone before the first song
    if (player.currentIndex < 0) {
        if (player.loopPlaylist) {
            player.currentIndex = (int)player.playlist.size() - 1;
        } else {
            player.currentIndex = 0;
        }
    }

    playSong(player);
}

// ─── DISPLAY HEADER ─────────────────────────────────────────
void printHeader() {
    cout << FG_CYAN << BOLD;
    cout << "  +=======================================================+\n";
    cout << "  |        🎵  R E A L   M U S I C   P L A Y E R  🎵     |\n";
    cout << "  |              Windows Terminal Edition (wav)            |\n";
    cout << "  +=======================================================+\n";
    cout << RESET;
}

// ─── DISPLAY NOW PLAYING ─────────────────────────────────────
void printNowPlaying(const MusicPlayer& player) {
    if (player.playlist.empty()) {
        cout << FG_DGRAY << "  No songs loaded.\n" << RESET;
        return;
    }

    int actualIndex = player.playOrder[player.currentIndex];
    string name = player.songNames[actualIndex];
    string file = player.playlist[actualIndex];

    cout << FG_YELLOW << BOLD << "\n  NOW PLAYING\n" << RESET;
    cout << FG_WHITE << "  > " << name << FG_DGRAY << "  (" << file << ")\n" << RESET;

    // Status bar
    cout << "  ";
    if (player.isPlaying)
        cout << FG_GREEN << BOLD << "[ ▶ PLAYING ]" << RESET;
    else if (player.isPaused)
        cout << FG_ORANGE << BOLD << "[ ⏸ PAUSED  ]" << RESET;
    else
        cout << FG_DGRAY << "[ ■ STOPPED ]" << RESET;

    // Indicators
    cout << "  ";
    if (player.loopCurrent)
        cout << FG_PINK << "[🔂 LOOP]" << RESET << "  ";
    if (player.loopPlaylist)
        cout << FG_PINK << "[🔁 LOOP ALL]" << RESET << "  ";
    if (player.shuffleOn)
        cout << FG_CYAN << "[🔀 SHUFFLE]" << RESET;

    cout << "\n";
}

// ─── DISPLAY PLAYLIST ────────────────────────────────────────
void printPlaylist(const MusicPlayer& player) {
    cout << FG_YELLOW << BOLD << "\n  PLAYLIST\n" << RESET;
    cout << FG_DGRAY << "  ─────────────────────────────────────\n" << RESET;

    for (int i = 0; i < (int)player.playOrder.size(); i++) {
        int actualIndex = player.playOrder[i];

        // Highlight the current song
        if (i == player.currentIndex) {
            cout << FG_GREEN << BOLD << "  > [" << (i + 1) << "] "
                 << player.songNames[actualIndex] << RESET << "\n";
        } else {
            cout << FG_LGRAY << "    [" << (i + 1) << "] "
                 << player.songNames[actualIndex] << RESET << "\n";
        }
    }

    cout << FG_DGRAY << "  ─────────────────────────────────────\n" << RESET;
}

// ─── DISPLAY MENU ────────────────────────────────────────────
void printMenu() {
    cout << FG_CYAN << BOLD << "\n  CONTROLS\n" << RESET;
    cout << FG_LGRAY;
    cout << "  [1] Play       [2] Pause/Resume   [3] Stop\n";
    cout << "  [4] Next       [5] Previous\n";
    cout << "  [6] Toggle Loop (current song)\n";
    cout << "  [7] Toggle Loop Playlist\n";
    cout << "  [8] Toggle Shuffle\n";
    cout << "  [9] Jump to song #\n";
    cout << "  [0] Exit\n";
    cout << RESET;
    cout << FG_DGRAY << "  ─────────────────────────────────────\n" << RESET;
    cout << FG_WHITE << "  Enter choice: " << RESET;
}

// ─── MAIN ────────────────────────────────────────────────────
int main() {
    initConsole();

    MusicPlayer player;
    loadPlaylist(player);

    // Build default play order
    // (already done inside loadPlaylist via playOrder.push_back)

    int choice = -1;

    while (true) {
        clearScreen();
        printHeader();
        printNowPlaying(player);
        printPlaylist(player);
        printMenu();

        cin >> choice;

        switch (choice) {

            case 1: // Play current song
                playSong(player);
                break;

            case 2: // Pause or Resume
                togglePause(player);
                break;

            case 3: // Stop
                stopSong(player);
                break;

            case 4: // Next song
                nextSong(player);
                break;

            case 5: // Previous song
                prevSong(player);
                break;

            case 6: // Toggle loop current song
                player.loopCurrent = !player.loopCurrent;
                // If currently playing, restart with new loop setting
                if (player.isPlaying) playSong(player);
                break;

            case 7: // Toggle loop playlist
                player.loopPlaylist = !player.loopPlaylist;
                break;

            case 8: // Toggle shuffle
                player.shuffleOn = !player.shuffleOn;
                if (player.shuffleOn) {
                    shufflePlaylist(player);
                } else {
                    // Restore original order
                    player.playOrder.clear();
                    for (int i = 0; i < (int)player.playlist.size(); i++) {
                        player.playOrder.push_back(i);
                    }
                    player.currentIndex = 0;
                }
                break;

            case 9: { // Jump to specific song
                cout << FG_WHITE << "  Jump to song # (1-"
                     << player.playlist.size() << "): " << RESET;
                int jumpTo;
                cin >> jumpTo;
                jumpTo--;  // convert to 0-based index

                if (jumpTo >= 0 && jumpTo < (int)player.playlist.size()) {
                    player.currentIndex = jumpTo;
                    playSong(player);
                } else {
                    cout << FG_RED << "  Invalid song number!\n" << RESET;
                    Sleep(1000);
                }
                break;
            }

            case 0: // Exit
                stopSong(player);
                clearScreen();
                cout << FG_CYAN << BOLD
                     << "\n  Thanks for using RealMusicPlayer! 🎵\n\n"
                     << RESET;
                return 0;

            default:
                cout << FG_RED << "  Invalid choice!\n" << RESET;
                Sleep(800);
                break;
        }
    }

    return 0;
}

