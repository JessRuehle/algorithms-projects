#include<iostream>
#include "table.h"


namespace jlr {


    // the constructor was one of my more interesting uses of AI in this project.
    // Initially, I just made a for loop to initialize the table, however I forgot to
    // properly allocate memory for the table. I turned to ChatGPT's version and saw it
    // was written like this with a separate method called allocateMemory() as the only
    // code in the body. I asked ChatGPT if moving the allocated memory body straight
    // into the constructor body without breaking it, and it told me yes and updated its
    // code.
    // I'd never seen a member initializer list like this before, so I asked the ai to
    // tell me what it was, and it explained it to me. I rewrote it by removing it and
    // inside the method putting rows = this->rows, cols = this->cols, etc. When I ran
    // the program, I returned a badalloc() error. Upon asking the ai if it was
    // possible to initialize the variables in the body of the program, it gave me a
    // long explanation saying that yes, you can, but you may run into memory allocation
    // errors. It's prediction was correct and so I switched back to leaving the
    // variables initialized in the member list
    template<typename T>
    Table<T>::Table(int rows, int cols) : rows(rows), cols(cols), table_data(nullptr) {
        table_data = new T *[rows];
        for (int i = 0; i < rows; i++) {
            table_data[i] = new T[cols];
        }
    }


    // similarly to the constructor, this method also just contained a method called
    // deallocateMemory(). Upon conferring with ChatGPT, it said I could safely insert
    // the code for that method into the destructor's function body.
    template<typename T>
    Table<T>::~Table() {

        // if the table is not empty
        if (table_data != nullptr) {

            // iterate through the rows deleting each array stored at every index
            for (int i = 0; i < rows; i++) {
                delete[] table_data[i];
            }

            // finally, delete the remaining table
            delete[] table_data;
        }
    }

    template<typename T>
    Table<T>::Table(int n) : rows(n), cols(n), table_data(nullptr)  {
        table_data = new T *[rows];
        for (int i = 0; i < rows; i++) {
            table_data[i] = new T[cols];
        }
    }

    template<typename T>
    Table<T> Table<T>::append_cols(const Table<T> &other) {

        // if the two tables do not have the same amount of rows, throw an exception
        if (rows != other.rows) {
            throw std::runtime_error("Number of rows must match for column append.");
        }

        // new table to store the result of appending the previous table
        Table<T> result(rows, cols + other.cols);

        // iterate through the array, setting each index of the resultant table equal
        // to the original table's data
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = table_data[i][j];
            }

            // iterate through the columns of the other table and append them to the
            // resultant table
            for (int j = 0; j < other.cols; j++) {
                result(i, cols + j) = other(i, j);
            }
        }

        // return the resulting table
        return result;
    }

    template<typename T>
    Table<T> Table<T>::append_rows(const Table<T> &other) {

        // if the two tables do not have the same number of columns, throw an exception
        if (cols != other.cols) {
            throw std::runtime_error("Number of columns must match for row append.");
        }

        // new table to store the result of appending the previous table
        Table<T> result(rows + other.rows, cols);

        // iterate through the array, setting each index of the resultant table equal
        // to the original table's data
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = table_data[i][j];
            }
        }

        // iterate through the rows of the other table and append them to the
        // resultant table
        for (int i = 0; i < other.rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(rows + i, j) = other(i, j);
            }
        }

        // return the resulting table
        return result;
    }

    template <typename T>
    Table<T> Table<T>::operator()(int startRow, int startCol, int endRow, int endCol)
            const {

        // filter out potential out-of-bounds indexing and throw an exception if there
        // is one
        if (startRow < 0 || startRow >= rows || startCol < 0 || startCol >= cols ||
            endRow < 0 || endRow >= rows || endCol < 0 || endCol >= cols ||
            startRow > endRow || startCol > endCol) {
            throw std::invalid_argument("Invalid subtable parameters.");
        }

        // create a new table to store the subtable in
        int subtableRows = endRow - startRow + 1;
        int subtableCols = endCol - startCol + 1;
        Table<T> subtable(subtableRows, subtableCols);

        // iterate through the original table from the beginning row and column to the
        // ending one, adding the data to the new subtable
        for (int i = startRow; i <= endRow; i++) {
            for (int j = startCol; j <= endCol; j++) {
                subtable(i - startRow, j - startCol) = table_data[i][j];
            }
        }

        // return the new table
        return subtable;
    }

    template<typename T>
    T &Table<T>::operator()(int row, int col) {
        // check to make sure the requested row and column are not out of bounds. if
        // they aren't, return the data at the table's row and column. otherwise, throw
        // an exception
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return table_data[row][col];
        } else {
            throw std::out_of_range("Row or column index is out of bounds.");
        }
    }

    template<typename T>
    const T &Table<T>::operator()(int row, int col) const {
        // check to make sure the requested row and column are not out of bounds. if
        // they aren't, return the data at the table's row and column. otherwise, throw
        // an exception
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            return table_data[row][col];
        } else {
            throw std::out_of_range("Row or column index is out of bounds.");
        }
    }

    template <typename T>
    Table<T> Table<T>::operator+(T (*func)(T)) const {

        // new resultant table
        Table<T> result(rows, cols);

        // iterates through table adding data to each element after executing a
        // function on that data at each location
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result(i, j) = func(table_data[i][j]);
            }
        }

        // return the resulting table
        return result;
    }
}

