#ifndef __h_list__
#define __h_list__

/*
 * Struct for a list that is capable of saving the first and last name of a person.
 * succ is a pointer on the next node in the list
 * data is a void pointer on the data which is to be saved in the list
 */
struct node{
	struct node *succ;
	void *data;
};

typedef struct node* List;

/*
 * This function can insert a struct node, that is already filled with the names, at the right place in a list
 * The list can be empty, then the new_node will be inserted at the first position
 * If there are already elements in the list, the new_entry will be inserted such that the list is alphabetically ordered by last name.
 * If there are two people with the same last_name the first_name is the next  for sorting.
 * If there are two people with the same first_name and last_name the position will be before the first occurrence of duplicates. 
 */
List insert_sorted(List list, void* new_entry, int (*is_smaller)(void*, void*));

/*
 * Allocates memory for a new struct node and returns a pointer on the allocated memory.
 */
List new_node(void);

/*
 * Prints the list.
 */
void print_list(List, void (*print_entry(void*)));

/*
 * Frees a list, including all the memory allocated for the structs and the elements of the structs.
 */
void free_list(List, void (*free_node)(void*));


#endif

