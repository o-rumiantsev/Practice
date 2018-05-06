#include <iostream>
#include <vector>
#include "bst.h"

using namespace std;

int main() {
  BST tree;

  tree.generate(10, 1, 10);
  tree.print();

  int count = 0;
  vector<int> uniq = tree.uniq(&count);

  for (int i = 0; i < count; ++i) cout << uniq[i] << " ";
  cout << endl;

  return 0;
}
