#include "person.h"

/*
 *Compairing criterion: name
 *
 */
int name_is_smaller(struct node* p1, struct node* p2) {
	/*Compare first names*/
	if(compare_strings(p1->last_name, p2->last_name) == Smaller) 
		return 1;
	/*If the first names are equal compare the last names*/
	if(compare_strings(p1->last_name, p2->last_name) == Equal 
	&& compare_strings(p1->first_name, p2->first_name) == Smaller) 
		return 1;
	return 0;
}

void free_struct_person(struct node* node){
	free(node->last_name);
	free(node->first_name);
	free(node);
	return;
}