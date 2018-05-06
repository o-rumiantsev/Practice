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
  int _uniq(Node *, int);
  void get_uniq(Node *, std::vector<int> *);

public:
  BST();
  Node *find(int);
  Node *insert(int);
  void print();
  void remove(int);
  void clear();
  void generate(int, int, int);
  std::vector<int> uniq(int *);
};

#endif
