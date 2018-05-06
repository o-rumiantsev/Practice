#include <vector>
#ifndef bst_h
#define bst_h

class Node;

class BST {
private:
  Node *root;
  Node *_find(Node *, int);
  Node *_find_min(Node *);
  Node *_insert(Node *, int);
  void _print(Node *);
  void _remove(Node *);
  void _remove_root();
  void _clear(Node *);
  void get_uniq(Node *, std::vector<int> *);
  void get_most_frequent(Node *, int, std::vector<int> *);
  int count_frequency(Node *);

public:
  BST();
  Node *find(int);
  Node *insert(int);
  void print();
  void remove(int);
  void clear();
  void generate(int, int, int);
  std::vector<int> uniq();
  std::vector<int> most_frequent();
};

#endif
