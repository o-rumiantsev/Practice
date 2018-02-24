#ifndef arraylike_h
#define arraylike_h

typedef struct node_s node;
typedef struct list_s list;

list *init(int);
void push(list *, int);
list *from_array(int *, int);
void insert(list *, int, int);
void node_remove(list *, int);
void print_list(list *);

#endif
