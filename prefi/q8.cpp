#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int main() {

    vector<pair<string,int>> scores;

    string name;
    int score;

    // read existing file (if wala pa, ok lang empty)
    ifstream in("scores.txt");
    while(in >> name >> score){
        scores.push_back({name, score});
    }
    in.close();

    // display existing
    cout << "Current scores:\n";
    for(auto s : scores){
        cout << s.first << " " << s.second << endl;
    }

    // add new
    cout << "\nenter name and score: ";
    cin >> name >> score;

    scores.push_back({name, score});

    // rewrite file
    ofstream out("scores.txt");
    for(auto s : scores){
        out << s.first << " " << s.second << endl;
    }
    out.close();

    // find highest
    int maxScore = scores[0].second;
    string best = scores[0].first;

    for(auto s : scores){
        if(s.second > maxScore){
            maxScore = s.second;
            best = s.first;
        }
    }

    cout << "\nTop: " << best << " " << maxScore << endl;

    return 0;
}
