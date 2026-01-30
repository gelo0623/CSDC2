#include <iostream>
using namespace std;

// Function definition goes here
// [WRITE YOUR FUNCTION HERE]
float calculateAverage(int temps[], int size) {
    int sum = 0;
    float average = 0.0;
    
    for (int i = 0; i < size; i++){
        sum += temps[i];
    }
    
    average = sum / size;
    
    return average;
}

int main() {
    // Declare and initialize the temperatures array
    int temperatures[7] = {28, 31, 29, 33, 30, 27, 32};
    float avgtemp;
    
    
    
    // Call the function and store result
    avgtemp = calculateAverage(temperatures, 7);
    
    
    // Display the result
    cout << "Average Temperature: " << avgtemp << "°C" << endl;
    
    return 0;
}
