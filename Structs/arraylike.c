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

// Initialize list root
//
//
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

// Push to the end of the list
//
//
void push(list *ls, int data) {
  node *new_node = (node *)malloc(sizeof(node));
  node *tmp = ls->root;
  while (tmp->next) tmp = tmp->next;
  new_node->data = data;
  new_node->index = tmp->index + 1;
  tmp->next = new_node;
  ++ls->len;
}

// Make list from array
//
//
list *from_array(int *arr, int len) {
  list *l = init(arr[0]);
  for (int i = 1; i < len; ++i) push(l, arr[i]);
  return l;
};

// Insert into list after
// element with appropriate
// index
//
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

// Remove node with
// appropriate index
//
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

// Print list to console
//
//
void print_list(list *ls) {
  node *p = ls->root;
  printf("List <");
  for (int i = 0; i < ls->len; ++i) {
    if (p->next) printf("%d, ", p->data);
    else printf("%d>\n", p->data);
    p = p->next;
  }
}
