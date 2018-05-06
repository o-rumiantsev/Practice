#include <iostream>
#include <vector>
#include "bst.h"

using namespace std;

int main() {
  BST tree;

  tree.generate(11, 1, 10);
  tree.print();

  vector<int> frequent = tree.most_frequent();
  int count = frequent.size();

  for (int i = 0; i < count; ++i) cout << frequent[i] << " ";
  cout << endl;

  return 0;
}
