#include <iostream>
#include <vector>
#include "bst.h"

using namespace std;

class Node {
public:
  int value;
  Node *parent;
  Node *left;
  Node *right;

  Node(Node *parent_node, int x) {
    value = x;
    parent = parent_node;
    left = NULL;
    right = NULL;
  }
};

BST::BST() {
  root = NULL;
}

Node *BST::_find(Node *node, int value) {
  if (!node || node->value == value) return node;

  if (value > node->value) return _find(node->right, value);
  else return _find(node->left, value);
}

Node *BST::_find_min(Node *node) {
  if (node->left) return _find_min(node->left);
  return node;
}

Node *BST::_insert(Node *node, int value) {
  if (value > node->value) {
    if (node->right) return _insert(node->right, value);
    else {
      node->right = new Node(node, value);
      return node->right;
    }
  } else {
    if (node->left) return _insert(node->left, value);
    else {
      node->left = new Node(node, value);
      return node->left;
    }
  }
}

void BST::_print(Node *node) {
  if (node) {
    cout << node->value << endl;

    if (node->left) cout << node->left->value << " ";
    else cout << node->left << " ";

    if (node->right) cout << node->right->value;
    else cout << node->right;

    cout << endl;

    _print(node->left);
    _print(node->right);
  }
}

void BST::_remove(Node *node) {
  // Whether node has no children
  //
  if (!node->left && !node->right) {
    if (node == node->parent->left) node->parent->left = NULL;
    else node->parent->right = NULL;
    delete node;
    return;
  }

  // Whether node has one child
  //
  if (
    (!node->left && !!node->right) ||
    (!!node->left && !node->right)
  ) {
    Node *child = node->left ? node->left : node->right;
    cout << "removing with one child" << endl;
    if (node == node->parent->left) node->parent->left = child;
    else node->parent->right = child;
    child->parent = node->parent;
    delete node;
  }

  // Whether node has two children
  //
  Node *minimum = _find_min(node->right);
  node->value = minimum->value;

  if (minimum->parent->left == minimum)
    minimum->parent->left = minimum->right;
  else minimum->parent->right = minimum->right;

  delete minimum;
}

void BST::_remove_root() {
  // Whether root has no children
  //
  if (!root->left && !root->right) {
    delete root;
    return;
  }

  // Whether root has one child
  //
  if (
    (!root->left && !!root->right) ||
    (!!root->left && !root->right)
  ) {
    Node *child = root->left ? root->left : root->right;
    root = child;
    return;
  }

  // Whether node has two children
  //
  Node *minimum = _find_min(root->right);
  root->value = minimum->value;

  if (minimum->parent->left == minimum)
    minimum->parent->left = minimum->right;
  else minimum->parent->right = minimum->right;

  delete minimum;
}

void BST::_clear(Node *node) {
  if (node->left) _clear(node->left);
  if (node->right) _clear(node->right);
  delete node;
}

void BST::get_uniq(Node *node, vector<int> *uniq_values) {
  if (!node) return;

  bool equal_after = !!_find(node->left, node->value);
  bool equal_before = find(node->value) != node;

  if (!equal_after && !equal_before) uniq_values->push_back(node->value);

  get_uniq(node->left, uniq_values);
  get_uniq(node->right, uniq_values);
}

int BST::count_frequency(Node *node) {
  Node *temp = node;
  int count = 0;

  while (temp) {
    temp = _find(temp->left, temp->value);
    ++count;
  }

  return count;
}

void BST::get_most_frequent(
  Node *node,
  int most_frequent_value,
  vector<int> *most_frequent
) {
  if (!node) return;

  bool uniq_value = find(node->value) == node;
  int self_frequency;

  if (uniq_value) {
    self_frequency = count_frequency(node);
    if (self_frequency > most_frequent_value) {
      most_frequent_value = self_frequency;
      most_frequent->clear();
      most_frequent->push_back(node->value);
    } else if (self_frequency == most_frequent_value) {
      most_frequent->push_back(node->value);
    }
  }

  if (node->left) get_most_frequent(
    node->left, most_frequent_value, most_frequent
  );

  if (node->right) get_most_frequent(
    node->right, most_frequent_value, most_frequent
  );


}

Node *BST::find(int value) {
  return _find(root, value);
}

Node *BST::insert(int value) {
  if (!root) {
    root = new Node(NULL, value);
    return root;
  }

  return _insert(root, value);
}

void BST::print() {
  _print(root);
}

void BST::remove(int value) {
  Node *node = find(value);
  node == root ? _remove_root() : _remove(node);
}

void BST::clear() {
  _clear(root);
  root = NULL;
}

void BST::generate(int count, int start, int end) {
  int range = end - start;
  srand(time(NULL));

  int i;
  for (i = 0; i < count; ++i) {
    int random_number = rand() % range + start;
    insert(random_number);
  }
}

vector<int> BST::uniq() {
  vector<int> uniq_values;
  get_uniq(root, &uniq_values);

  return uniq_values;
}

vector<int> BST::most_frequent() {
  vector<int> most_frequent;

  get_most_frequent(root, 0, &most_frequent);

  return most_frequent;
}
