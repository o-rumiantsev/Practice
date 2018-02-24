#include <stdio.h>
#include <stdlib.h>
#include "arraylike.h"

struct node_s {
  int data;
  int index;
  struct node_s *next;
};

struct list_s {
  node *root;
  int len;
};


void _inc_after(node *nd) {
  while (nd->next) {
    nd = nd->next;
    ++nd->index;
  }
}

void _dec_after(node *nd) {
  while (nd->next) {
    nd = nd->next;
    --nd->index;
  }
}

list *init(int data) {
  list *ls = (list*)malloc(sizeof(list));
  node *nd;
  nd = (node*)malloc(sizeof(node));
  nd->data = data;
  nd->index = 0;
  nd->next = NULL;
  ls->root = nd;
  ls->len = 1;
  return ls;
}

void push(list *ls, int data) {
  node *new_node = (node *)malloc(sizeof(node));
  node *tmp = ls->root;
  while (tmp->next) tmp = tmp->next;
  new_node->data = data;
  new_node->index = tmp->index + 1;
  tmp->next = new_node;
  ++ls->len;
}

void insert(list *ls, int index, int data) {
  node *tmp, *p,
         *nd = ls->root;
  while (nd->index != index) nd = nd->next;
  p = nd->next;
  tmp = (node*)malloc(sizeof(node));
  nd->next = tmp;
  tmp->index = ++index;
  tmp->next = p;
  tmp->data = data;
  _inc_after(tmp);
  ++ls->len;
}

void node_remove(list *ls, int index) {
  node *nd = ls->root,
              *tmp, *p;
  while (nd->next->index != index) nd = nd->next;
  p = nd->next->next;
  tmp = nd->next;
  free(tmp);
  --p->index;
  nd->next = p;
  _dec_after(p);
  --ls->len;
}

void print_list(list *ls) {
  node *p = ls->root;
  printf("[");
  for (int i = 0; i < ls->len; ++i) {
    if (p->next) printf("%d, ", p->data);
    else printf("%d]\n", p->data);
    p = p->next;
  }
}
