#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

/**
 * Determines the possible number of paths that can get to the target block of the
 * pyramid determined by the user. This is accomplished two ways - first by recursive
 * backtracking, then utilizing dynamic programming.
 *
 * @author Jessica Ruehle
 */

/**
 * Recursively checks every path to target row and column and documents the number of
 * paths it takes to get there.
 */
void check(int row, int col, int target_row, int target_col, int &paths);

int main(int argc, char *argv[]) {

    int paths = 0; // number of paths to target block
    int target_row, target_col, size;

    target_row = atoi(argv[1]);
    target_col = atoi(argv[2]);
    size = target_row;

    // recursive search
    auto startRecursion = high_resolution_clock::now(); // start timer
    check(1, 1, target_row, target_col, paths);
    auto endRecursion = high_resolution_clock::now(); // end timer

    // calculated the time to complete the search and print results
    auto durationRecursion = duration_cast<microseconds>(endRecursion - startRecursion);
    cout << "Number of paths via recursive search: " << paths << endl;
    cout << "Time elapsed: " << durationRecursion.count() << " microseconds" << endl;

    // Create array of ints
    int **arr = new int*[size];

    auto startDynamic = high_resolution_clock::now(); // start timer

    // traverse array starting at second row, since the starting row will only have one
    // index, and build the staggered 2d array
    for(int i = 1; i < size; i++) {
        arr[i] = new int[i + 1];
    }

    // initialize first and last columns to 1s
    for(int i = 0; i < size; i++) {
        arr[i][0] = 1;
        arr[i][i] = 1;
    }

    // fill array starting at the first inner index. loop should never write to first
    // and last indices of array. add the upper left and right blocks to current one
    for(int i = 2; i < size; i++) {
        for(int j = 1; j < i; j++) {

            // calculate value of block based on previous two blocks
            arr[i][j] = arr[i - 1][j - 1] + arr[i - 1][j];
        }
    }

    auto endDynamic = high_resolution_clock::now(); // end timer

    // calculated the time to complete the search and print results
    auto durationDynamic = duration_cast<microseconds>(endDynamic - startDynamic);
    cout << "Number of paths via dynamic programming: ";
    cout << arr[target_row - 1][target_col - 1] << endl;
    cout << "Time elapsed: " << durationDynamic.count() << " microseconds" << endl;

    // delete the array
    delete[] arr;

    return 0;
}

/*
 * Check implementation
 */
void check(int row, int col, int targetRow, int targetCol, int &paths) {

    // if the current block is the target one, increment the number of paths
    if (row == targetRow && col == targetCol) {
        paths++;

    // if still within the bounds of the pyramid, check down to the left and right
    } else if (row + 1 <= targetRow) {

        // check down
        check(row + 1, col, targetRow, targetCol, paths);
        // check diagonally right
        check(row + 1, col + 1, targetRow, targetCol, paths);
    }

    // if the bottom of the pyramid is reached, and it is not the target, just return
}