#include <string>
#ifndef structs_h
#define structs_h

using namespace std;

struct stack_node;

class stack {
private:
  stack_node *head, *tail;
  int size;

public:
  stack();
  stack_node* first() { return head; }
  stack_node* last() { return tail; }
  void push(string data);
  void unshift(string data);
  string pop();
  void remove(string data);
  void print();
  void clear();
  int length();
};

stack concat_sl(stack x, stack y);


struct deque_node;

class deque {
private:
  deque_node *head, *tail;
  int size;

public:
  deque();
  deque_node* first() { return head; }
  deque_node* last() { return tail; }
  void push(string data);
  void unshift(string data);
  string pop();
  string shift();
  void remove(string data);
  void print();
  void clear();
  int length();
};

deque concat_dl(deque x, deque y);

#endif
