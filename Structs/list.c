#include <stdio.h>
#include <stdlib.h>


// ----- One-linked list -----

struct node {
  int data;
  struct node *next;
};

// Initialize list root
//
//
struct node *init_oll(int data) {
  struct node *nd;
  nd = (struct node*)malloc(sizeof(struct node));
  nd->data = data;
  nd->next = NULL;
  return nd;
}

// Add new node to list
//
//
struct node *add_node_oll(struct node *nd, int data) {
  struct node *tmp, *p;
  tmp = (struct node*)malloc(sizeof(struct node));
  p = nd->next;
  nd->next = tmp;
  tmp->data = data;
  tmp->next = p;
  return tmp;
}

// Remove node from list
//
//
struct node *remove_node_oll(struct node *nd, struct node *root) {
  struct node *tmp;
  tmp = root;
  while (tmp->next != nd) tmp = tmp->next;
  tmp->next = (nd->next) ? nd->next : NULL;
  free(nd);
  return tmp;
}

// Rmove list root
//
//
struct node *root_remove_oll(struct node *root) {
  struct node *tmp;
  tmp = root->next;
  free(root);
  return tmp;
}

// Swap two nodes
//
//
struct node *swap_oll(
  struct node *nd1,
  struct node *nd2,
  struct node *root
) {
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

// Copy list
//
//
struct node *copy_oll(struct node *root) {
  struct node *tmp = root;
  struct node *new_root = init_oll(tmp->data);
  struct node *new_tmp = new_root;
  while (tmp->next) {
    add_node_oll(new_tmp, tmp->next->data);
    new_tmp = new_tmp->next;
    tmp = tmp->next;
  }
  return new_root;
}

// Print list nodes to console
//
//
void print_oll(struct node *root) {
  struct node *p = root;
  do {
    printf("%d ", p->data);
    p = p->next;
  } while (p != NULL);
  printf("\n");
}


// ----- Two-linked list -----

struct node_tll {
  int data;
  struct node_tll *prev;
  struct node_tll *next;
};

// Initialize list root
//
//
struct node_tll *init_tll(int data) {
  struct node_tll *nd;
  nd = (struct node_tll *)malloc(sizeof(struct node_tll));
  nd->data = data;
  nd->next = NULL;
  nd->prev = NULL;
  return nd;
}

// Add node to list
//
//
struct node_tll *add_node_tll(struct node_tll *nd, int data) {
  struct node_tll *tmp, *p;
  tmp = (struct node_tll *)malloc(sizeof(struct node_tll));
  p = nd->next;
  nd->next = tmp;
  tmp->data = data;
  tmp->next = p;
  tmp->prev = nd;
  if (p != NULL) p->prev = tmp;
  return tmp;
}

// Remove node from list
//
//
struct node_tll *remove_node_tll(struct node_tll *nd) {
  struct node_tll *prev = nd->prev,
                  *next = nd->next;
  if (prev != NULL) prev->next = next;
  if (next != NULL) next->prev = prev;
  free(nd);
  return prev;
}

// Remove root from list
//
//
struct node_tll *root_remove_tll(struct node_tll *root) {
  struct node_tll *tmp;
  tmp = root->next;
  tmp->prev = NULL;
  free(root);
  return tmp;
}

// Swap two nodes
//
//
struct node_tll *swap_tll(
  struct node_tll *nd1,
  struct node_tll *nd2,
  struct node_tll *root
) {
  struct node_tll *prev1, *prev2, *next1, *next2;
  prev1 = nd1->prev;
  prev2 = nd2->prev;
  next1 = nd1->next;
  next2 = nd2->next;
  if (nd2 == next1) {
    nd2->next = nd1;
    nd2->prev = prev1;
    nd1->next = next2;
    nd1->prev = nd2;
    if (next2 != NULL) next2->prev = nd1;
    if (prev1 != root) prev1->next = nd2;
  } else if (nd1 == next2) {
    nd1->next = nd2;
    nd1->prev = prev2;
    nd2->next = next1;
    nd2->prev = nd1;
    if (next1 != NULL) next1->prev = nd2;
    if (prev2 != root) prev2->next = nd1;
  } else {
    if (nd1 != root) prev1->next = nd2;
    nd2->next = next1;
    if (nd2 != root) prev2->next = nd1;
    nd1->next = next2;
    nd2->prev = prev1;
    if (next2 != NULL) next2->prev = nd1;
    nd1->prev = prev2;
    if (next1 != NULL) next1->prev = nd2;
  }
  if (nd1 == root) return nd2;
  if (nd2 == root) return nd1;
  return root;
}

// Copy list
//
//
struct node_tll *copy_tll(struct node_tll *root) {
  struct node_tll *tmp = root;
  struct node_tll *new_root = init_tll(tmp->data);
  struct node_tll *new_tmp = new_root;
  while (tmp->next) {
    add_node_tll(new_tmp, tmp->next->data);
    new_tmp = new_tmp->next;
    tmp = tmp->next;
  }
  return new_root;
}

// Print list nodes to console
//
//
void print_tll(struct node_tll *root) {
  struct node_tll *p = root;
  do {
    printf("%d ", p->data);
    p = p->next;
  } while (p != NULL);
  printf("\n");
};

// Print list nodes reverse to console
//
//
void print_tll_reverse(struct node_tll *root) {
  struct node_tll *p = root;
  while (p->next != NULL) p = p->next;
  do {
    printf("%d ", p->data);
    p = p->prev;
  } while (p != NULL);
  printf("\n");
};
