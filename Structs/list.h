#ifndef list_h
#define list_h


// One-linked list
//
struct node;
struct node *init_oll(int);
struct node *add_node_oll(struct node *, int);
struct node *remove_node_oll(struct node *, struct node *);
struct node *root_remove_oll(struct node *);
struct node *swap_oll(struct node *, struct node *, struct node *);
struct node *copy_oll(struct node *);
void print_oll(struct node *);

// Two-linked list
//
struct node_tll;
struct node_tll *init_tll(int);
struct node_tll *add_node_tll(struct node_tll *, int);
struct node_tll *remove_node_tll(struct node_tll *, struct node_tll *);
struct node_tll *root_remove_tll(struct node_tll *);
struct node_tll *swap_tll(
  struct node_tll *,
  struct node_tll *,
  struct node_tll *
);
struct node_tll *copy_tll(struct node_tll *);
void print_tll(struct node_tll *);
void print_tll_reverse(struct node_tll *);

#endif
