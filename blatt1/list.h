#ifndef __h_list__
#define __h_list__

struct node{
	struct node *succ;
	char *last_name;
	char *first_name;
};

struct node * insert_sorted(struct node* list, struct node* new_entry);

struct node * new_node();

void print_list(const struct node*);

void free_node(struct node*);

void free_list(struct node*);












#endif