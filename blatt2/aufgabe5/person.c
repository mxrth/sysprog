#include "person.h"
#include "mystring.h"
#include <stdlib.h>
#include <stdio.h>

/*
 *Compairing criterion: name
 *
 */
int name_is_smaller(struct person* p1, struct person* p2) {
	/*Compare first names*/
	if(compare_strings(p1->last_name, p2->last_name) == Smaller) 
		return 1;
	/*If the first names are equal compare the last names*/
	if(compare_strings(p1->last_name, p2->last_name) == Equal 
	&& compare_strings(p1->first_name, p2->first_name) == Smaller) 
		return 1;
	return 0;
}

/*
 *Compairing criterion: town
 *
 */
int town_is_smaller(struct person* p1, struct person* p2) {
	/*Compare twon*/
	if(compare_strings(p1->town, p2->town) == Smaller){
		return 1;
	}
	else return 0;
}

int birthdate_is_smaller(struct person* p1, struct person* p2){
	if(p1->date.year<p2->date.year){
		return 1;
	}
	if(p1->date.year==p2->date.year && p1->date.month<p2->date.month){
		return 1;
	}
	if(p1->date.year==p2->date.year && p1->date.month==p2->date.month && p1->date.day<p2->date.day){
		return 1;
	}
	return 0;
}

void print_person(struct person* p){
	printf("%s %s %d.%d.%d %s\n",p->first_name,p->last_name,p->date.day,p->date.month,p->date.year,p->town);
};

/*Assumptions: node is a valid struct person*
 *
 *Result: Frees the memory allocated for the strings last_name, first_name, town
 *After this it frees the struct
 */
void free_struct_person(struct person* node){
	free(node->last_name);
	free(node->first_name);
	free(node->town);
	free(node);
	return;
}