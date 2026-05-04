#include <iostream>
#include <string>
using namespace std;

/* ===================== 1. Diamond Star Pattern ===================== */
void diamondPattern(int n) {
    // Upper half
    for (int i = 1; i <= n; i += 2) {
        for (int j = 0; j < (n - i) / 2; j++) cout << " ";
        for (int j = 0; j < i; j++) cout << "*";
        cout << endl;
    }

    // Lower half
    for (int i = n - 2; i >= 1; i -= 2) {
        for (int j = 0; j < (n - i) / 2; j++) cout << " ";
        for (int j = 0; j < i; j++) cout << "*";
        cout << endl;
    }
}

/* ===================== 2. GCD (Euclid) ===================== */
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* ===================== 3. Multiplication Table ===================== */
void multiplicationTable(int n, int limit) {
    for (int i = 1; i <= limit; i++) {
        cout << n << " x " << i << " = " << n * i << endl;
    }
}

/* ===================== 4. PIN Validator ===================== */
void pinValidator() {
    int pin;
    do {
        cout << "Enter PIN: ";
        cin >> pin;

        if (pin != 1234) {
            cout << "Wrong PIN. Try again." << endl;
        }

    } while (pin != 1234);

    cout << "Access granted." << endl;
}

/* ===================== 5. Power (Recursion) ===================== */
int power(int base, int exp) {
    if (exp == 0) return 1;
    if (exp == 1) return base;
    return base * power(base, exp - 1);
}

/* ===================== 6. Reverse String (Recursion) ===================== */
string reverseString(string s) {
    if (s.length() <= 1) return s;
    return reverseString(s.substr(1)) + s[0];
}

/* ===================== 7. Count Occurrences (Recursion) ===================== */
int countOccurrences(int arr[], int size, int x) {
    if (size == 0) return 0;

    if (arr[size - 1] == x)
        return 1 + countOccurrences(arr, size - 1, x);
    else
        return countOccurrences(arr, size - 1, x);
}

/* ===================== 8. Digital Root (Recursion) ===================== */
int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

int digitalRoot(int n) {
    if (n < 10) return n;
    return digitalRoot(digitSum(n));
}

/* ===================== MAIN FUNCTION ===================== */
int main() {
    cout << "===== 1. Diamond Pattern =====" << endl;
    diamondPattern(5);

    cout << "\n===== 2. GCD =====" << endl;
    cout << gcd(48, 18) << endl;

    cout << "\n===== 3. Multiplication Table =====" << endl;
    multiplicationTable(5, 5);

    cout << "\n===== 4. PIN Validator =====" << endl;
    // pinValidator(); // Uncomment to test interactive

    cout << "\n===== 5. Power =====" << endl;
    cout << power(2, 10) << endl;

    cout << "\n===== 6. Reverse String =====" << endl;
    cout << reverseString("hello") << endl;

    cout << "\n===== 7. Count Occurrences =====" << endl;
    int arr[] = {1, 3, 3, 5, 3, 7};
    cout << countOccurrences(arr, 6, 3) << endl;

    cout << "\n===== 8. Digital Root =====" << endl;
    cout << digitalRoot(9875) << endl;

    return 0;
}
