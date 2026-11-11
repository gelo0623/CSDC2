#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

vector<int> sorted;
mutex m;

// Each number sleeps for its value in seconds, then joins the sorted list
void sleepSort(int x) {
    this_thread::sleep_for(chrono::milliseconds(x * 1000 + 100));

    lock_guard<mutex> lock(m);
    sorted.push_back(x);
    cout << "⏰ " << x << " woke up after " << x << " seconds and was sorted!\n";
}

int main() {
    int n;
    cout << "=== Welcome to the Sleep Sort (C++) ===\n";
    cout << "Enter size: ";
    cin >> n;

    int a[100];
    int biggest = 0;
    cout << "Enter " << n << " values separated by spaces: ";
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] > biggest) biggest = a[i];
    }

    cout << "\n🚀 Starting the sorting process... Watch the timer!\n";
    auto start = chrono::high_resolution_clock::now();

    // Start one thread per number
    vector<thread> t;
    for (int i = 0; i < n; i++)
        t.push_back(thread(sleepSort, a[i]));

    // Count the seconds
    for (int s = 1; s <= biggest; s++) {
        this_thread::sleep_for(chrono::seconds(1));
        lock_guard<mutex> lock(m);
        cout << "⏱️  Second " << s << "\n";
    }

    for (int i = 0; i < n; i++)
        t[i].join();

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> total = end - start;

    cout << "\n=== Sorting Complete! ===\n";
    cout << "Your sorted list: [ ";
    for (int x : sorted)
        cout << x << " ";
    cout << "]\n";
    cout << "Total time elapsed: " << total.count() << " seconds\n";
    return 0;
}
