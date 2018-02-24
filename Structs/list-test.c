#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void test_oll();
void test_tll();

int main() {
  printf("\n----- TEST ONE-LINKED LIST -----\n");
  test_oll();
  printf("\n----- TEST TWO-LINKED LIST -----\n");
  test_tll();
  return 0;
}

void test_oll() {
  struct node *a = init_oll(10);
  struct node *b = add_node_oll(a, 20);
  struct node *c = add_node_oll(b, 30);
  struct node *d = add_node_oll(c, 40);
  struct node *e = add_node_oll(d, 50);
  printf("List:           ");
  print_oll(a);

  struct node *new_root = copy_oll(a);
  printf("Copied list:    ");
  print_oll(new_root);

  struct node *f = swap_oll(a, e, a);
  printf("Swap 10 and 50: ");
  print_oll(f);

  remove_node_oll(b, f);
  printf("Remove node 20: ");
  print_oll(f);

  struct node *g = root_remove_oll(f);
  printf("Remove root:    ");
  print_oll(g);

  printf("Copied list:    ");
  print_oll(new_root);
}

void test_tll() {
  struct node_tll *a = init_tll(10);
  struct node_tll *b = add_node_tll(a, 20);
  struct node_tll *c = add_node_tll(b, 30);
  struct node_tll *d = add_node_tll(c, 40);
  struct node_tll *e = add_node_tll(d, 50);
  printf("List:           ");
  print_tll(a);

  printf("List reverse:   ");
  print_tll_reverse(a);

  struct node_tll *new_root = copy_tll(a);
  printf("Copied list:    ");
  print_tll(new_root);

  struct node_tll *f = swap_tll(a, e, a);
  printf("Swap 10 and 50: ");
  print_tll(f);

  remove_node_tll(b, f);
  printf("Remove node 20: ");
  print_tll(f);

  struct node_tll *g = root_remove_tll(f);
  printf("Remove root:    ");
  print_tll(g);

  printf("Copied list:    ");
  print_tll(new_root);
}
