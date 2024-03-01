/*
 * Test program for AvlTree class. See execution snapshot below at end of file.
 *
 * Author: Drue Coles
 */

#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include "avl_tree.cpp"


using namespace std;

void test(BST<int>*, int[], int);

int main() {
    int keys[] = {80, 70, 60, 85, 10, 75, 50, 65, 66, 67, 68, 69};
    const int n = 12;

//    cout << "Non-rebalancing BST:" << endl;
//    test(new BST<int>(), keys, n);

    cout << "\nAVL tree:" << endl;
    test(new AvlTree<int>(), keys, n);

    return 0;
}

void test(BST<int>* p, int keys[], int n) {
    for (int i = 0; i < n; i++) {
        cout << "Inserting " << keys[i] << ": ";
        p->insert(keys[i]);
        cout << *p << "(height = " << p->height() << ")" << endl;
    }
}

/*
Non-rebalancing BST:
Inserting 80: 80 (height = 0)
Inserting 70: 70 80 (height = 1)
Inserting 60: 60 70 80 (height = 2)
Inserting 85: 60 70 80 85 (height = 2)
Inserting 10: 10 60 70 80 85 (height = 3)
Inserting 75: 10 60 70 75 80 85 (height = 3)
Inserting 50: 10 50 60 70 75 80 85 (height = 4)
Inserting 65: 10 50 60 65 70 75 80 85 (height = 4)
Inserting 66: 10 50 60 65 66 70 75 80 85 (height = 4)
Inserting 67: 10 50 60 65 66 67 70 75 80 85 (height = 5)
Inserting 68: 10 50 60 65 66 67 68 70 75 80 85 (height = 6)
Inserting 69: 10 50 60 65 66 67 68 69 70 75 80 85 (height = 7)

AVL tree:
Inserting 80: 80 (height = 0)
Inserting 70: 70 80 (height = 1)
Inserting 60: 60 70 80 (height = 1)
Inserting 85: 60 70 80 85 (height = 2)
Inserting 10: 10 60 70 80 85 (height = 2)
Inserting 75: 10 60 70 75 80 85 (height = 2)
Inserting 50: 10 50 60 70 75 80 85 (height = 2)
Inserting 65: 10 50 60 65 70 75 80 85 (height = 3)
Inserting 66: 10 50 60 65 66 70 75 80 85 (height = 3)
Inserting 67: 10 50 60 65 66 67 70 75 80 85 (height = 3)
Inserting 68: 10 50 60 65 66 67 68 70 75 80 85 (height = 3)
Inserting 69: 10 50 60 65 66 67 68 69 70 75 80 85 (height = 3)
*/