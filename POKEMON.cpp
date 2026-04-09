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

struct GigaImpact {
    string name; 
    string type;
    string category;   
    int power;
    int accuracy;
    int pp;
    bool isContact;
};

struct HyperBeam {
    string name; 
    string type;
    string category;   
    int power;
    int accuracy;
    int pp;
    bool isContact;
};

struct Earthquake {
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
    
    int choice;
    
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

cout << "What will " << snorlax.name << " do?" << endl;
cout << "[1] FIGHT   [2] BAG  \n[3]POKEMON  [4] RUN\n";
cout << "Enter Choice: ";
cin >> choice;




if (choice == 1){
    
    int choice1;
    


	BodySlam attack;
	GigaImpact attack1;
	HyperBeam attack2;
	Earthquake attack3;
	
	attack.pp = 15;
	attack1.pp = 15;
	attack2.pp = 15;
	attack3.pp = 15;
	
	
	
	cout << "====================================" << endl;
	cout << "==          YOUR ATTACKS           ==" << endl;
	cout << "====================================" << endl;
	cout << "[1] BODY SLAM" << " (PP: " << attack.pp << ")" << endl;
	cout << "[2] GIGA IMPACT" << " (PP: " << attack1.pp << ")" << endl;
	cout << "[3] HYPER BEAM" << " (PP: " << attack2.pp << ")" << endl;
	cout << "[4] EARTHQUAKE" << " (PP: " << attack3.pp << ")" << endl;
	cout << "Enter move: ";
	cin >>choice1;
	
	
	if (choice1 == 1){
	attack.name       = "Body Slam";
	attack.type       = "Normal";
	attack.category      = "Physical";
	attack.power     =  85;
	attack.accuracy         = 100;
	attack.pp    = 15;
	attack.isContact      = true;
	
	cout << "Attack:    " << attack.name << endl;
	cout << "PP:        " << attack.pp << endl;
	cout << "Type:      " << attack.type << endl;
	cout << "Category:  " << attack.category << endl;
	cout << "Power:     " << attack.power << endl;
	cout << "Accuracy:  " << attack.accuracy << endl;
	cout << "Status:    " << (attack.isContact ? "Hit" : "Miss") << endl;
	
	}
	
	if (choice1 == 2){
	attack1.name       = "Giga Impact";
	attack1.type       = "Normal";
	attack1.category      = "Physical";
	attack1.power     =  85;
	attack1.accuracy         = 100;
	attack1.pp    = 15;
	attack1.isContact      = true;
	
	cout << "Attack:    " << attack1.name << endl;
	cout << "PP:        " << attack1.pp << endl;
	cout << "Type:      " << attack1.type << endl;
	cout << "Category:  " << attack1.category << endl;
	cout << "Power:     " << attack1.power << endl;
	cout << "Accuracy:  " << attack1.accuracy << endl;
	cout << "Status:    " << (attack1.isContact ? "Hit" : "Miss") << endl;
	
	}
	
	
	if (choice == 3){
	attack2.name       = "Hyper Beam";
	attack2.type       = "Normal";
	attack2.category      = "Physical";
	attack2.power     =  85;
	attack2.accuracy         = 100;
	attack2.pp    = 15;
	attack2.isContact      = true;
	
	cout << "Attack:    " << attack2.name << endl;
	cout << "PP:        " << attack2.pp << endl;
	cout << "Type:      " << attack2.type << endl;
	cout << "Category:  " << attack2.category << endl;
	cout << "Power:     " << attack2.power << endl;
	cout << "Accuracy:  " << attack2.accuracy << endl;
	cout << "Status:    " << (attack2.isContact ? "Hit" : "Miss") << endl;
	
	}
	
	
	
	if (choice == 4){
	attack3.name       = "Earthquake";
	attack3.type       = "Normal";
	attack3.category      = "Physical";
	attack3.power     =  85;
	attack3.accuracy         = 100;
	attack3.pp    = 15;
	attack3.isContact      = true;
	
	cout << "Attack:    " << attack3.name << endl;
	cout << "PP:        " << attack3.pp << endl;
	cout << "Type:      " << attack3.type << endl;
	cout << "Category:  " << attack3.category << endl;
	cout << "Power:     " << attack3.power << endl;
	cout << "Accuracy:  " << attack3.accuracy << endl;
	cout << "Status:    " << (attack3.isContact ? "Hit" : "Miss") << endl;
	
	}
	




}

if (choice == 2){
    
    
}

if (choice == 3){
    
    
}

if (choice == 4){
    cout << "You have ran away safely.\n";
    cin.get(); cin.get();
    
    break;
}



	return 0;
}
