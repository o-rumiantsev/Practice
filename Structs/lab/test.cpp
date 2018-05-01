#include <iostream>
#include "list.h"

using namespace std;

void test_SL();
void test_DL();

int main() {
  test_SL();
  test_DL();
  return 0;
}

void test_SL() {
  List_SL *list = new List_SL();

  list->push(10);
  list->push(20);
  list->push(30);
  list->push(40);
  list->push(50);
  list->push(60);
  list->push(70);
  list->print();

  List_SL *copied = copy(list);
  list->print();
  copied->print();
}

void test_DL() {
  List_DL *list = new List_DL();

  list->push(10);
  list->push(20);
  list->push(30);
  list->push(40);
  list->push(50);
  list->push(60);
  list->push(70);
  list->print();

  List_DL *copied = copy(list);
  list->print();
  copied->print();
}
