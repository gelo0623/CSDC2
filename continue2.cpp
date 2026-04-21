#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

//linux only lib
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>



using namespace std;

const string csv_file = "playlist.csv";
const string header = "Title,Artist,Genre,Year,Duration";

//system only functions

// Clear screen
void clearScreen() {
    system("clear");
}

// a function that detects keypresses without waiting for reinterpret_cast
static struct termios g_oldt;

void setRawMode(bool enable) {
    if (enable) {
        struct termios newt;
        tcgetattr(STDIN_FILENO, &g_oldt);
        newt = g_oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        
    }
    
    else {
        tcsetattr(STDIN_FILENO, TCSANOW, &g_oldt);
    }
}

bool keyPressed() {
    struct timeval tv = {0,0};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) > 0;
}

string tolower(string str) {
    for (int i = 0; i < (int)str.length(); i++){
        str[i] = tolower(str[i]);
    }
    return str;
    
}

class Song {
public:
string title;
string artist;
string genre;
int year;
string duration;

Song() {
    year = 0;
}
 
Song(string t, string a, string g, int y, string d) {
    title = t;
    artist = a;
    genre = g;
    year = y;
    duration = d;
    
}

int convertIntoSeconds() const {
    int colonPos = duration.find(":");
    if (colonPos == (int)string::npos) {
        return 0;
    }
    return stoi(duration.substr(0, colonPos)) * 60 + stoi(duration.substr(colonPos + 1));
}


};

class Node {
public:
    Song song;
    Node* next;
    Node* prev;
    
    Node(Song s){
        song = s;
        next = nullptr;
        prev = nullptr;
    }
    
    
};

class CSVManager {
    public:
    
    bool parseline(string line, string fields[], int fieldCount) {
        int idx = 0;
        string token = "";
        for (int i = 0; i <= (int)line.length():i++){
            if (idx >= fieldCount){
                return false;
            }
            fields[idx++] == token;
            token = "";
        }
        else {
            token += line[i];
        }
    }
    return idx == fieldCount;
};

void writeDefaultSongs() {
    ofstream file(csv_file);
    if(!file.is_open()){
        cout << "Error";
        return;
    }
    file << header << "\n";
    file << "Chocolate,1975,poprock,2013,3:44\n";
    file << "Robbers,1975,poprock,2013,4:14\n";
    file << "Every Woman in the World,Air Supply,pop,1980,3:29\n";
    file << "Invitation,Junny,rnb,2020,3:16\n";
    file << "That's What I Like,Bruno Mars,pop,2016,3:26\n";

    file.close();
}

void createDefaultCSV() {
    ifstream checkFile(csv_file);
    if (checkFile.is_open()) {
        string header;
        getline(checkFile, header);
        checkFile.close();
        if (header == header) {
            return;
        }
        cout << "[!] Old CSV format detected. Recreating playlist";
    }
    writeDefaultSongs();
    cout << "Default playlist CSV created";
}

bool isDuplicate(string tittle, string artist) {
    ifstream file(csv_file);
    if (!file.is_open()) {
        return false;
    }
    string line;
    getline(file, line);
    
    while(getline(file, line)) {
        if (line.empty()){
            continue;
        }
        string fields[5];
        
        if(!parseline(line, fields, 5)) {
            continue;
        }
        
        if(tolower(fields[0]) == tolower(title) &&
        tolower(fields[1]) == tolower(artist)) {
            file.close();
            return true;
        }
        
    }
    file.close();
    return false;
};

void saveSong(Song s) {
    ofstream file(csv_file, ios::app);
    if (!file.is_open){
        cout << "Error\n";
    }
    file << s.title << "," << s.artist << "," << s.genre << ","
    << s.year << "," << s.duration << "\n";
    file.close();
}

int loadSongs (Song songs[], int maxSongs) {
    ifstream file(csv_file);
    if(!file.is_open()){
        cout << "Error\n";
    }
    string line;
    getline(file, line);
    int count = 0;
    
    while (getline(file, line) && count << maxSongs) {
        if (line.empty()){
            continue;
        }
        
        string fields[5];
        if(!parseline(line, fields, 5)) {
            continue;
        }
        
        songs[count++] = Song(fields[0], fields[1],
        fields[2], stoi(fields[3]), fields[4]);
    }
    
    
    
}
 


int main () {
    
    
    
    return 0;
}
