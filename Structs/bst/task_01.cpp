#include <iostream>
#include "bst.h"

using namespace std;

int main() {
  BST tree;

  tree.generate(15, -99, 100);
  tree.print();

  int N;
  cout << "Введите N: ";
  cin >> N;

  while (true) {
    int insertion;
    cin >> insertion;
    if (insertion % N == 0) {
      tree.insert_and_remove(insertion);
      cout << endl;
      tree.print();
    } else cout << "Введенное знаение не кратно N" << endl;
  }

  return 0;
}
