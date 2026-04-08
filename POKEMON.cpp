#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

struct Character {
	string name;
	string type;
	int level;
	int attack;
	int hp;
	int speed;

};

struct Enemy {
    string name;          
    string type;           
    int    level;         
    int    attack;    
    int    hp; 
    int speed;
    bool   isDefeated;     
    
};


struct BodySlam {
    string name; 
    string type;
    string category;   
    int power;
    int accuracy;
    int pp;
    bool isContact;
};





int main() {
    
    srand(time(0));
    
    int x = 5, y = 1;
    
    char move;
    
    while(true) {
        system("clear");
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 15; j++){
                
                if (i == y && j == x)
                cout << "V";
                
                else 
                cout << "*";
                
            }
            cout << endl;
        }
        
        
        cout << "Move(WSAD): ";
        cin >> move;
        
        if (move == 'w' && y > 0) y--;
        if (move == 's' && y < 2) y++;
        if (move == 'a' && x > 0) x--;
        if (move == 'd' && x < 14) x++;
        
        if (rand() % 5 == 0) {
    cout << "A wild pokemon has appeared!\n";
    cin.ignore();
    cin.get();
    break; 
}
        
    }
    
	Character snorlax;
	cout << "====================================" << endl;
	cout << "==         YOUR POKEMON           ==" << endl;
	cout << "====================================" << endl;
	
	snorlax.name       = "Snorlax";
	snorlax.type       = "Normal";
	snorlax.level      = 50;
	snorlax.attack     =  146;
	snorlax.hp         = 251;
	snorlax.speed      = 66;

	cout << "Pokemon: " << snorlax.name << endl;
	cout << "Type:      " << snorlax.type << endl;
	cout << "Level:     " << snorlax.level << endl;
	cout << "Attack:    " << snorlax.attack << endl;
	cout << "HP:        " << snorlax.hp << endl;
	cout << "Speed:     " << snorlax.speed << endl;

cout << "\n";

	Enemy squirtle;
	cout << "====================================" << endl;
	cout << "==           YOUR ENEMY           ==" << endl;
	cout << "====================================" << endl;
	
	squirtle.name       = "Squirtle";
	squirtle.type       = "Water";
	squirtle.level      = 50;
	squirtle.attack     =  84;
	squirtle.hp         = 135;
	squirtle.speed      = 79;
	squirtle.isDefeated = true;

	cout << "Pokemon:   " << squirtle.name << endl;
	cout << "Type:      " << squirtle.type << endl;
	cout << "Level:     " << squirtle.level << endl;
	cout << "Attack:    " << squirtle.attack << endl;
	cout << "HP:        " << squirtle.hp << endl;
	cout << "Speed:     " << squirtle.speed << endl;
	cout << "Status:    " << (squirtle.isDefeated ? "Alive" : "Fainted") << endl;


cout << "\n";



	BodySlam attack;
	cout << "====================================" << endl;
	cout << "==          YOUR ATTACK           ==" << endl;
	cout << "====================================" << endl;
	
	attack.name       = "Body Slam";
	attack.type       = "Normal";
	attack.category      = "Physical";
	attack.power     =  85;
	attack.accuracy         = 100;
	attack.pp    = 15;
	attack.isContact      = true;

	cout << "Attack:    " << attack.name << endl;
	cout << "Type:      " << attack.type << endl;
	cout << "Category:  " << attack.category << endl;
	cout << "Power:     " << attack.power << endl;
	cout << "Accuracy:  " << attack.accuracy << endl;
	cout << "PP:        " << attack.pp << endl;
	cout << "Status:    " << (attack.isContact ? "Hit" : "Miss") << endl;
	return 0;
}
