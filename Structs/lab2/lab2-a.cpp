#include <iostream>
#include <vector>
#include "bst.h"

using namespace std;

int main() {
  BST tree;

  tree.generate(10, 1, 10);
  tree.print();

  vector<int> uniq = tree.uniq();

  int count = uniq.size();
  for (int i = 0; i < count; ++i) cout << uniq[i] << " ";
  cout << endl;

  return 0;
}
