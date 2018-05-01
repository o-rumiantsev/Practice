#include <iostream>
#include "list.h"

using namespace std;

// ---- Single-linked list ----

struct Node_SL {
  int data;
  Node_SL *next;
};

List_SL::List_SL() {
  head = NULL;
  tail = NULL;
};

void List_SL::push(int data) {
  Node_SL* node = new Node_SL;
  node->data = data;
  node->next = NULL;

  if (!head) {
    head = node;
    tail = node;
  } else {
    tail->next = node;
    tail = tail->next;
  }
};

void List_SL::remove(int data) {
  if (!head) return;

  if (head->data == data) {
    Node_SL *node;
    node = head;
    head = node->next;
    delete node;
    return;
  }

  Node_SL *temp = head;
  Node_SL *node;

  while (temp->next->data != data) {
    temp = temp->next;
  }

  node = temp->next;
  temp->next = node->next;
  delete node;
};


void List_SL::print() {
  if (!head) {
    cout << "< Empty >" << endl;
    return;
  }

  Node_SL *node = head;

  while (node) {
    cout << node->data << " -> ";
    node = node->next;
  }

  cout << "\b\b\b\b    " << endl;
};

void List_SL::clear() {
  Node_SL *node;

  while (head) {
    node = head;
    head = head->next;
    delete node;
  }
};

List_SL *copy(List_SL *list) {
  List_SL *copy = new List_SL();
  Node_SL *node = list->head;

  while (node) {
    copy->push(node->data);
    node = node->next;
  }

  list->clear();
  return copy;
};

// ---- Double-linked list ----

struct Node_DL {
  int data;
  Node_DL* prev;
  Node_DL* next;
};

List_DL::List_DL() {
  head = NULL;
  tail = NULL;
};

void List_DL::push(int data) {
  Node_DL* node = new Node_DL;
  node->data = data;
  node->prev = NULL;
  node->next = NULL;

  if (!head) {
    head = node;
    tail = head;
  } else {
    tail->next = node;
    node->prev = tail;
    tail = node;
  }
};

void List_DL::unshift(int data) {
  Node_DL* node = new Node_DL;
  node->data = data;
  node->prev = NULL;
  node->next = NULL;

  if (!head) {
    head = node;
    tail = head;
  } else {
    head->prev = node;
    node->next = head;
    head = node;
  }
};

int List_DL::pop() {
  Node_DL *node = tail;
  tail = tail->prev;
  tail->next = NULL;
  return node->data;
}

int List_DL::shift() {
  Node_DL *node = head;
  head = head->next;
  head->prev = NULL;
  return node->data;
}

void List_DL::remove(int data) {
  if (head->data == data) {
    this->shift();
    return;
  } else if (tail->data == data) {
    this->pop();
    return;
  }

  Node_DL *temp = head;

  while (temp->next->data != data) {
    temp = temp->next;
  }

  Node_DL *node = temp->next;
  temp->next = node->next;
  node->next->prev = temp;
  delete node;
};

void List_DL::print() {
  if (!head) {
    cout << "< Empty >" << endl;
    return;
  }

  Node_DL *node = head;

  while (node) {
    cout << node->data << " -> ";
    node = node->next;
  }

  cout << "\b\b\b\b    " << endl;
};

void List_DL::clear() {
  Node_DL *node;

  while (head) {
    node = head;
    head = head->next;
    delete node;
  }
};

List_DL *copy(List_DL *list) {
  List_DL *copy = new List_DL();
  Node_DL *node = list->head;

  while (node) {
    copy->push(node->data);
    node = node->next;
  }

  list->clear();
  return copy;
}
