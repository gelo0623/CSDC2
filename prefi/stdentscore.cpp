#include <iostream>
#include <string>
#include <fstream>

using namespace std;



int main () {
    
    ifstream infile("scores.txt");
    if (!infile) {
        ofstream create("scores.txt");
        create.close();
    }
    infile.close();
    
    
    string names[6767];
    int scores[6767];
    int count = 0;
    
    ifstream readfile("scores.ttxt");
    
    while (readfile >> names[count] >> scores[count]){
        count++;
    }
    
    readfile.close();
    
    cout << "Current Scores: " << endl;
    for (int i = 0; i < count; i++) {
        cout << names[i] << " = " << scores[i] << endl;
    }
    
    string newPlayer;
    int scorenew;
    
    cout << "Enter new player: ";
    cin >> newPlayer;
    
    cout << "Enter new score: ";
    cin >> scorenew;
    
    names[count] = newPlayer;
    scores[count] = scorenew;
    count++;
    
    ofstream outfile("scores.txt");
    
    for (int i = 0; i < count; i++) {
        outfile << names[i] << " " << scores[i] << endl;
    }
    
    outfile.close();
    
    int Highestindex = 0;
    
    for(int i = 0; i < count; i++) {
        if (scores[i] > scores[Highestindex]) {
            Highestindex = i;
        }
    }
    
    cout << "Highest Score: " << endl;
    cout << names[Highestindex] << " = " << scores[Highestindex] << endl;
    
    

    return 0;
}
