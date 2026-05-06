#include <iostream>
#include <string>

using namespace std;



int main() {

	int n, x;
	int sum = 0;
	double average;
	int passcount = 0;

	cout << "Enter number of elements: ";
	cin >> n;


	int arr[n];

	cout << "Enter elements: ";
	for (int i = 0; i < n; i++) {
		cin >> arr[i];

		sum += arr[i];
		if (arr[i] >= 60) {
			passcount++;
		}


	}

	average = (double)sum / n;


	int largest = arr[0];


	for (int i = 1; i < n; i++) {
		if (arr[i] > largest) {
			largest = arr[i];
		}
	}

	int smallest = arr[0];

	for (int i = 1; i < n; i++) {
		if (arr[i] < smallest) {
			smallest = arr[i];
		}
	}






	cout << "Largest: " << largest << endl;
	cout << "Smallest: " << smallest << endl;
	cout << "Average: " << average << endl;
	cout << "Passed: " << passcount << endl;





	return 0;
}
