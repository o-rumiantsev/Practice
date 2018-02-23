#include <stdio.h>
#include <stdlib.h>


struct node {
  int data;
  struct node *next;
};


struct node *init(int a) {
  struct node *ls;
  ls = (struct node*)malloc(sizeof(struct node));
  ls->data = a;
  ls->next = NULL;
  return (ls);
}


struct node *add_node(struct node *ls, int data) {
  struct node *tmp, *p;
  tmp = (struct node*)malloc(sizeof(struct node));
  p = ls->next;
  ls->next = tmp;
  tmp->data = data;
  tmp->next = p;
  return tmp;
}


struct node *remove_node(struct node *ls, struct node *root) {
  struct node *tmp;
  tmp = root;
  while (tmp->next != ls) tmp = tmp->next;
  tmp->next = (ls->next) ? ls->next : NULL;
  free(ls);
  return tmp;
}


struct node *root_remove(struct node *root) {
  struct node *tmp;
  tmp = root->next;
  free(root);
  return tmp;
}


struct node *swap(struct node *nd1, struct node *nd2, struct node *root) {
  struct node *prev1, *prev2, *next1, *next2;
  prev1 = root;
  prev2 = root;
  next1 = nd1->next;
  next2 = nd2->next;
  if (prev1 == nd1) prev1 = NULL;
  else while (prev1->next != nd1) prev1 = prev1->next;
  if (prev2 == nd2) prev2 = NULL;
  else while (prev2->next != nd2) prev2 = prev2->next;
  if (nd2 == next1) {
    nd2->next = nd1;
    nd1->next = next2;
    if (nd1 != root) prev1->next = nd2;
  } else if (nd1 == next2) {
    nd1->next = nd2;
    nd2->next = next1;
    if (nd2 != root) prev2->next = nd1;
  } else {
    if (nd1 != root) prev1->next = nd2;
    nd2->next = next1;
    if (nd2 != root) prev2->next = nd1;
    nd1->next = next2;
  }
  if (nd1 == root) return nd2;
  if (nd2 == root) return nd1;
  return root;
}


void print_list(struct node *root) {
  struct node *p = root;
  do {
    printf("%d ", p->data);
    p = p->next;
  } while (p != NULL);
  printf("\n");
}


int main() {
  struct node *a = init(10);
  struct node *b = add_node(a, 20);
  struct node *c = add_node(b, 30);
  struct node *d = add_node(c, 40);
  struct node *e = add_node(d, 50);
  print_list(a);

  struct node *f = swap(a, e, a);
  print_list(f);

  remove_node(b, f);
  print_list(f);

  struct node *g = root_remove(f);
  print_list(g);
}
