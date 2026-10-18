#include <iostream>
using namespace std;

// ---------------------------------------------------------
// 1. SEQUENTIAL SEARCH  (PDF: SeqSearch)
// list: array, last: index of the last element, target: item to find
// location: index where the target was found (or last if not found)
// ---------------------------------------------------------
bool seqSearch(int list[], int last, int target, int &location) {
    int looker = 0;

    while (looker < last && target != list[looker]) {
        looker++;
    }

    location = looker;
    return (target == list[looker]);
}

// ---------------------------------------------------------
// 2. SENTINEL SEARCH  (PDF: SentinelSearch)
// The array must have ONE EXTRA slot after the last element
// ---------------------------------------------------------
bool sentinelSearch(int list[], int last, int target, int &location) {
    list[last + 1] = target;      // put the target at the end (the sentinel)

    int looker = 0;
    while (target != list[looker]) {
        looker++;
    }

    if (looker <= last) {         // stopped inside the real list
        location = looker;
        return true;
    } else {                      // stopped on the sentinel
        location = last;
        return false;
    }
}

// ---------------------------------------------------------
// 3. PROBABILITY SEARCH  (PDF: ProbabilitySearch)
// When found, the item swaps with the one before it (moves up one place)
// ---------------------------------------------------------
bool probabilitySearch(int list[], int last, int target, int &location) {
    int looker = 0;
    bool found;

    while (looker < last && target != list[looker]) {
        looker++;
    }

    if (target == list[looker]) {
        found = true;
        if (looker > 0) {
            int temp = list[looker - 1];
            list[looker - 1] = list[looker];
            list[looker] = temp;
            looker = looker - 1;
        }
    } else {
        found = false;
    }

    location = looker;
    return found;
}

// ---------------------------------------------------------
// 4. ORDERED LIST SEARCH  (PDF: OrderedSearch)
// The list must be sorted (small to large)
// ---------------------------------------------------------
bool orderedSearch(int list[], int last, int target, int &location) {
    int looker;

    if (target < list[last]) {
        looker = 0;
        while (target > list[looker]) {
            looker++;
        }
    } else {
        looker = last;
    }

    location = looker;
    return (target == list[looker]);
}

// ---------------------------------------------------------
// 5. BINARY SEARCH  (PDF: BinarySearch)
// The list must be sorted (small to large)
// ---------------------------------------------------------
bool binarySearch(int list[], int end, int target, int &location) {
    int first = 0;
    int last = end;
    int mid = 0;

    while (first <= last) {
        mid = (first + last) / 2;

        if (target > list[mid]) {          // look in the upper half
            first = mid + 1;
        } else if (target < list[mid]) {   // look in the lower half
            last = mid - 1;
        } else {                           // found equal: force exit
            first = last + 1;
        }
    }

    location = mid;
    return (target == list[mid]);
}

// ---------------------------------------------------------
// Demo using the examples from the slides
// ---------------------------------------------------------
void show(const char* name, int target, bool found, int location) {
    cout << name << " (target " << target << "): "
         << (found ? "found" : "not found")
         << ", location " << location << endl;
}

int main() {
    int location;
    bool found;

    // Sequential: slide array
    int a[10] = {100, 23, 1, -3, 67, 88, 9, 10, 45, 77};
    found = seqSearch(a, 9, 67, location);
    show("Sequential ", 67, found, location);
    found = seqSearch(a, 9, 7, location);
    show("Sequential ", 7, found, location);

    // Sentinel: same array but with one extra slot (s[10])
    int s[11] = {100, 23, 1, -3, 67, 88, 9, 10, 45, 77};
    found = sentinelSearch(s, 9, 67, location);
    show("Sentinel   ", 67, found, location);
    found = sentinelSearch(s, 9, 7, location);
    show("Sentinel   ", 7, found, location);

    // Probability: found item moves up one place each search
    int p[10] = {100, 23, 1, -3, 67, 88, 9, 10, 45, 77};
    found = probabilitySearch(p, 9, 67, location);
    show("Probability", 67, found, location);
    found = probabilitySearch(p, 9, 67, location);
    show("Probability", 67, found, location);

    // Ordered list and binary: sorted slide array
    int b[12] = {4, 7, 8, 10, 14, 21, 22, 36, 62, 77, 81, 91};
    found = orderedSearch(b, 11, 22, location);
    show("Ordered    ", 22, found, location);
    found = orderedSearch(b, 11, 25, location);
    show("Ordered    ", 25, found, location);
    found = binarySearch(b, 11, 22, location);
    show("Binary     ", 22, found, location);
    found = binarySearch(b, 11, 25, location);
    show("Binary     ", 25, found, location);

    return 0;
}
