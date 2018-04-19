#ifndef list_h
#define list_h

// ---- Single-linked list ----

struct Node_SL;

class List_SL {
public:
  Node_SL *head, *tail;
  List_SL();
  void push(int);
  void remove(int);
  void print();
  void clear();
};

List_SL *copy(List_SL *);


// ---- Double-linked list ----

struct Node_DL;

class List_DL {
public:
  Node_DL *head, *tail;
  List_DL();
  void push(int);
  void unshift(int);
  int pop();
  int shift();
  void remove(int);
  void print();
  void clear();
};

List_DL *copy(List_DL *);

#endif
