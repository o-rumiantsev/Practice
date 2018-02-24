#include <stdio.h>
#include "arraylike.h"


int main() {
  list *l = init(10);
  push(l, 20);
  push(l, 30);
  push(l, 40);
  push(l, 50);
  push(l, 60);
  push(l, 70);
  push(l, 80);
  push(l, 90);
  push(l, 100);
  push(l, 110);
  push(l, 120);
  print_list(l);

  int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
  int len = sizeof(a) / sizeof(int);
  list *ls = from_array(a, len);
  print_list(ls);
}
