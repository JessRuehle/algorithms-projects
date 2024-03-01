
#ifndef HW1_TABLE_H
#define HW1_TABLE_H
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdexcept>

using namespace std;

/**
 * Template class that creates a table of type T. Provides methods that allow users to
 * read and modify table data.
 *
 ********************************************
 * Explanation of contribution from ChatGPT *
 ********************************************
 *
 * I unfortunately ran out of time to fully write this project by hand, so I utilized
 * ChatGPT to generate a large portion of the code for this project. I have never used
 * it prior to this experience, and have quite a few thoughts on it. Even with the
 * assistance of AI, this project still took multiple hours to complete, however a lot
 * of the boiler-plate-type code was generated on my behalf by the ai and saved me a
 * lot of time that I was able to spend on the bigger picture of the assignment.
 * This is an explanation of how I utilized ChatGPT to generate my code. Also, I am
 * uploading a pdf copy of my conversation with the ai in case you are interested in my
 * exact verbiage and it's exact responses.
 *
 * I first analyzed the output samples and test code programs by hand, singling out
 * methods used and potential argument types they took. After gathering some methods, I
 * gave ChatGPT all the output and test code and requested it make a class that could
 * be used for that code and generate that output.
 * I next asked it to separate everything into a header and implementation file. I then
 * realized I never specified that it should be a template class and requested it turn
 * it into one.
 * From analyzing the table_tester.cpp file, I saw that it missed two important
 * methods (get_rows and get_columns) and gave it a description of what they both do
 * and requested it add them to the code. It also lacked a call operator, and I
 * requested it add that as well. Next, I provided the table_tester.cpp program and
 * asked it to improve the class accordingly. However, it improved the test program
 * rather than the class.
 * When it initially made the class, it store the table in a vector, and I wanted it
 * store in a 2d array. So, I requested that it update the class and its functions
 * replacing the vector with a 2d array.
 * After that, I asked the AI to start removing unnecessary functions it generated from
 * its initial development of the class.
 * When it generated the code, it used some C++ techniques that I was unfamiliar with,
 * and asked it to break down certain functions I didn't understand so I could change
 * them to something I preferred or just to get a better understanding to write
 * accurate comments. The constructor was a place where I didn't totally understand
 * what it did, I go into more detail about that in the table.cpp file in the comment
 * above the constructor.
 * The ai really struggled to not make an independent function for the line
 *                                t = t(3, 5, 5, 7);
 * in the test code. It continually tried to make a function called extractSubtable
 * instead of overloading the () operator. After a few attempts with different wording,
 * it was eventually successful.
 * Finally, I asked it to write me an overloaded + operator based on the information
 * you gave us. It was successful and provided one.
 * Despite my extensive use of ChatGPT for this project, I still felt that an
 * understanding of how to write in C++ is crucial to the process. I made sure to
 * understand what was written by the ai so I could add documentation. Despite the code
 * being mostly ai-generated, all the comments are written by me.
 */

namespace jlr {
    template <typename T>
    class Table {
    public:

        // constructor
        Table<T>(int rows, int cols);

        // one argument constructor
        Table<T>(int size);

        // destructor
        ~Table<T>();

        // append columns from another table
        Table<T> append_cols(const Table<T>& other);

        // append rows from another table
        Table<T> append_rows(const Table<T>& other);

        // return the number of rows in the table
        int get_rows() const { return rows; }

        // return the number of columns in the table
        int get_cols() const { return cols; }

        // gives access to table data for reading and modifying
        T& operator()(int row, int col);

        // gives access to table data strictly for reading
        const T& operator()(int row, int col) const;

        // creates a subtable given 4 arguments for where to start and where to end
        Table<T> operator()(int startRow, int startCol, int endRow, int endCol) const;

        // overloaded + operator
        Table<T> operator+(T (*func)(T)) const;

        // overloads output operator the display table
        friend std::ostream& operator<<(std::ostream& out, const Table<T>& table) {

            // iterate through the table rows and columns
            for (int i = 0; i < table.get_rows(); i++) {
                for (int j = 0; j < table.get_cols(); j++) {
                    out << setw(4) << table(i, j);
                }
                out << endl;
            }
            return out;
        }

    private:
        int rows; // number of rows in table
        int cols; // number of columns in table
        T** table_data; // 2D array for table data.
    };
}

#endif