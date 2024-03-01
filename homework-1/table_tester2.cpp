/*
 * Test program for Table<string>.
 *
 * Author: Drue Coles
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include "table.cpp"
using namespace std;
using namespace jlr;

// fills table with random strings of specified length consisting
// of uppercase letters of the alphabet
void randomize(Table<string>&, int);

// fills table with a specified string
void fill(Table<string>&, const char*);

// returns a string identical to input string except that uppercase
// letters are converted to lowercase
string to_lower_case(string);

int main() {
    // initialize 5x5 table with random 3-letter strings
    Table<string> t(5);
    randomize(t, 3);
    cout << t << endl;

    // replace middle entry in table with spaces
    t(2, 2) = "   ";
    cout << t << endl;

    // append 3 columns
    Table<string> t2(5, 3); // 5 rows to match t
    fill(t2, "(+)");
    t = t.append_cols(t2); // now t has 8 columns
    cout << t << endl;

    // append 3 rows
    Table<string> t3(3, 8); // 8 columns to match t
    fill(t3, "(-)");
    t = t.append_rows(t3);
    cout << t << endl;

    // extract 5x5 subtable
    t = t(1, 1, 5, 5);
    cout << t << endl;
    cout << t + to_lower_case << endl;
    return 0;
}

// fills table with random strings of specified length consisting
// of uppercase letters of the alphabet
void randomize(Table<string>& t, int length) {
    for (int i = 0; i < t.get_rows(); i++) {
        for (int j = 0; j < t.get_cols(); j++) {
            string s = "";
            for (int k = 0; k < length; k++) {
                int offset = rand() % 26;
                t(i, j) += (char) ('A' + offset);
            }
        }
    }
}

// fills table with a specified string
void fill(Table<string>& t, const char* ptr) {
    for (int i = 0; i < t.get_rows(); i++) {
        for (int j = 0; j < t.get_cols(); j++) {
            t(i, j) = ptr;
        }
    }
}

// returns a string identical to input string except that uppercase
// letters are converted to lowercase
string to_lower_case(string s) {
    string t;
    for (char const& c : s) {
        t += isupper(c) ? c + ('a' - 'A') : c;
    }
    return t;
}