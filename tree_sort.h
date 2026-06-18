#include <iostream>
#include <vector>
#include "avl.h"

using namespace std;

int tree_sort() {
    cout << endl << "*** Ordenando usando BST/AVL *** " << endl;

    vector nums = {2, 7, 11, 15, 12, 1, 35, 16, 23, 5};

    AVLTree tree;

    for (const int v : nums) tree.insert(v);

    vector<int> sorted;

    tree.sort(sorted);

    cout << "Antes:  ";
    for (const int v : nums) {
        cout << v << " ";
    }
    cout << endl;

    cout << "Depois: ";
    for (const int v : sorted) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}