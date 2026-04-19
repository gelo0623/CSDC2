#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(){

    vector<string> n;
    vector<int> s;

    string name;
    int score;

    ifstream in("scores.txt");

    while(in >> name >> score){
        n.push_back(name);
        s.push_back(score);
    }
    in.close();

    cout << "scores:\n";
    for(int i=0;i<n.size();i++){
        cout << n[i] << " " << s[i] << endl;
    }

    cout << "\ninput: ";
    cin >> name >> score;

    n.push_back(name);
    s.push_back(score);

    ofstream out("scores.txt");
    for(int i=0;i<n.size();i++){
        out << n[i] << " " << s[i] << endl;
    }
    out.close();

    int max = s[0];
    string best = n[0];

    for(int i=0;i<n.size();i++){
        if(s[i] > max){
            max = s[i];
            best = n[i];
        }
    }

    cout << "\nbest: " << best << " " << max << endl;

    return 0;
}
