#include "arraylike.h"

int main() {
  list *l = init(10);
  insert(l, 0, 20);
  insert(l, 1, 30);
  insert(l, 2, 40);
  insert(l, 3, 50);
  insert(l, 4, 60);
  insert(l, 5, 70);
  push(l, 80);
  push(l, 90);
  push(l, 100);
  push(l, 110);
  push(l, 120);
  print_list(l);
}
