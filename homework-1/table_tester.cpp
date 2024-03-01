#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "table.cpp"
using namespace std;
using namespace jlr;

// fills table with random numbers in a specified range
void randomize(Table<int>&, int, int);

// fills table with a specified value
void fill(Table<int>&, int );

// returns the square of a number
int square(int);

int main() {
    // initialize table with random two-digit numbers
    const int ROWS = 5;
    const int COLS = 7;
    const int WIDTH = 4;
    Table<int> t(ROWS, COLS);
    randomize(t, 10, 99);
    cout << setw(WIDTH) << t << endl;

    // replace odd numbers in table with zero
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (t(i, j) % 2 == 1) {
                t(i, j) = 0;
            }
        }
    }
    cout << setw(WIDTH) << t << endl;

    // append 3 columns filled with -1
    Table<int> t2(ROWS, 3);
    fill(t2, -1);
    t = t.append_cols(t2);
    cout << setw(WIDTH) << t << endl;

    // append 2 rows filled with -2
    Table<int> t3(2, t.get_cols());
    fill(t3, -2);
    t = t.append_rows(t3);
    cout << setw(WIDTH) << t << endl;

    // extract a subtable
    t = t(3, 5, 5, 7);
    cout << setw(WIDTH) << t << endl;

    // square the entries in the table
    cout << setw(WIDTH) << t + square << endl;
    return 0;
}

// fills table with random numbers in [lo, hi].
void randomize(Table<int>& t, int lo, int hi) {
    for (int i = 0; i < t.get_rows(); i++) {
        for (int j = 0; j < t.get_cols(); j++) {
            t(i, j) = lo + rand() % (hi - lo + 1);
        }
    }
}

// fills table with val
void fill(Table<int>& t, int val) {
    for (int i = 0; i < t.get_rows(); i++) {
        for (int j = 0; j < t.get_cols(); j++) {
            t(i, j) = val;
        }
    }
}

int square(int k) {
    return k * k;
}