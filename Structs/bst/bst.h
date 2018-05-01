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
  void _clear(Node *);
  
public:
  BST();
  Node *find(int);
  Node *insert(int);
  void print();
  void remove(int);
  void clear();
  void generate(int, int, int);
  Node *insert_and_remove(int);
};

#endif
