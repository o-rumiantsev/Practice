#include <iostream>
#include <cstdlib>
#include "bst.h"

using namespace std;

int main() {
  BST tree;

  tree.generate(15, -99, 100);
  tree.print();

  while (true) {
    int insertion;
    cout << "Insert value: ";
    cin >> insertion;

    for (int i = 2; i < abs(insertion); ++i) {
      int mod = (unsigned)insertion % i;
      if (mod == 0) {
        tree.insert_and_remove(insertion);
        cout << endl;
        tree.print();
        break;
      }
    }
  }

  return 0;
}
