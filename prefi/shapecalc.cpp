#include <iostream>
#include <string>

using namespace std;


class  Rectangle {

private:
double height;
double width;
    
public:
Rectangle(double height1, double width1) {
    width = width1;
    height = height1;
    
}

double getArea() {
    return width * height;
}

double getPerimeter() {
    return 2 * (width + height);
    
}

bool isSquare () {
    return width == height;
    
}

    
};



int main () {
    
    double width1, height1;
    
    for (int i = 0; i< 3; i++){
        cout << "Rectangle #" << i + 1 << endl;
        
        cout << "Enter Width: ";
        cin >> width1;
        
        cout << "Enter Height: ";
        cin >> height1;
        
        Rectangle create(width1, height1);
        
        cout << "Area: " << create.getArea() << endl;
        cout << "Perimeter: " << create.getPerimeter() << endl;
        
        if (create.isSquare()){
            cout << "The square is square: " << endl;
            
        }
        
        else {
            cout << "This is not a square twin" << endl;
        }
    }
    
    
    return 0;
}

