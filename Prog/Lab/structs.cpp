#include <iostream>
#include <string>
#include "structs.h"

using namespace std;


struct stack_node {
  string data;
  stack_node *next;
};


stack::stack() {
  head = NULL;
  tail = NULL;
  size = 0;
}

void stack::push(string data) {
  stack_node* temp = new stack_node;
  temp->data = data;
  temp->next = NULL;

  if (!head) {
    head = temp;
    tail = temp;
  } else {
    tail->next = temp;
    tail = temp;
  }

  size++;
}

void stack::unshift(string data) {
  stack_node* temp = new stack_node;
  temp->data = data;
  temp->next = NULL;

  if (!head) {
    head = temp;
    tail = head;
  } else {
    temp->next = head;
    head = temp;
  }

  size++;
}

string stack::pop() {
  if (size == 0) return "";

  stack_node *temp;
  temp = head;

  if (size == 1) {
    head = NULL;
    tail = NULL;
    size = 0;
    return temp->data;
  }

  while (temp->next->data != tail->data) {
    temp = temp->next;
  }

  tail = temp->next;
  tail->next = NULL;
  size--;

  return temp->data;
}

void stack::remove(string data) {
  stack_node *temp;
  temp = head;

  if (temp->data == data) {
    stack_node *to_remove;
    to_remove = temp;
    head = to_remove->next;
    delete to_remove;
    return;
  } else if (!temp->next->next && tail->data == data) {
    temp->next = NULL;
    delete temp;
  }

  while (temp->next->data != data) {
    temp = temp->next;
  }

  stack_node *to_remove;
  to_remove = temp->next;
  temp->next = to_remove->next;
  size--;

  delete to_remove;
}

void stack::print() {
  stack_node *temp;
  temp = head;
  if (!temp) {
    cout << "e m p t y" << endl;
    return;
  }
  while (temp) {
    cout << temp->data << " -> ";
    temp = temp->next;
  }
  cout << "\b\b\b\b" << endl;
}

void stack::clear() {
  stack_node *temp;
  temp = head;

  while (head) {
    temp = head;
    head = head->next;
    delete temp;
  }

  size = 0;
}

int stack::length() {
  return size;
}

stack concat_sl(stack x, stack y) {
  stack res;
  stack_node *temp;

  temp = x.first();
  while (temp->next) {
    res.push(temp->data);
    temp = temp->next;
  }
  res.push(temp->data);

  temp = y.first();
  while (temp->next) {
    res.push(temp->data);
    temp = temp->next;
  }
  res.push(temp->data);

  return res;
}



struct deque_node {
  deque_node* prev;
  string data;
  deque_node* next;
};

deque::deque() {
  head = NULL;
  tail = NULL;
  size = 0;
}

void deque::push(string data) {
  deque_node* temp = new deque_node;
  temp->data = data;
  temp->prev = NULL;
  temp->next = NULL;

  if (!head) {
    head = temp;
    tail = head;
  } else {
    tail->next = temp;
    temp->prev = tail;
    tail = temp;
  }

  size++;
}

void deque::unshift(string data) {
  deque_node* temp = new deque_node;
  temp->data = data;
  temp->prev = NULL;
  temp->next = NULL;

  if (!head) {
    head = temp;
    tail = head;
  } else {
    head->prev = temp;
    temp->next = head;
    head = temp;
  }

  size++;
}

string deque::pop() {
  if (size == 0) return "";

  deque_node *temp;
  temp = tail;

  if (size == 1) {
    head = NULL;
    tail = NULL;
    size = 0;
    return temp->data;
  }

  tail = tail->prev;
  tail->next = NULL;
  size--;

  return temp->data;
}

string deque::shift() {
  if (size == 0) return "";

  deque_node *temp;
  temp = head;

  if (size == 1) {
    head = NULL;
    tail = NULL;
    size = 0;
    return temp->data;
  }

  head = head->next;
  head->prev = NULL;
  size--;

  return temp->data;
}

void deque::remove(string data) {
  deque_node *temp;
  temp = head;

  if (temp->data == data) {
    this->shift();
    return;
  } else if (tail->data == data) {
    this->pop();
    return;
  }

  while (temp->next->data != data) {
    temp = temp->next;
  }

  deque_node *to_remove;
  to_remove = temp->next;
  temp->next = to_remove->next;
  to_remove->next->prev = temp;
  size--;

  delete to_remove;
}

void deque::print() {
  deque_node *temp;
  temp = head;
  if (!temp) {
    cout << "e m p t y" << endl;
    return;
  }
  while (temp) {
    cout << temp->data << " -> ";
    temp = temp->next;
  }
  cout << "\b\b\b\b" << endl;
}

void deque::clear() {
  deque_node *temp;
  temp = head;

  while (head) {
    temp = head;
    head = head->next;
    delete temp;
  }

  size = 0;
}

deque concat_dl(deque x, deque y) {
  deque res;
  deque_node *temp;

  temp = x.first();
  while (temp->next) {
    res.push(temp->data);
    temp = temp->next;
  }
  res.push(temp->data);

  temp = y.first();
  while (temp->next) {
    res.push(temp->data);
    temp = temp->next;
  }
  res.push(temp->data);

  return res;
}

int deque::length() {
  return size;
}
