#ifndef __h_person__
#define __h_person__

/*
 *Struct for storing a date, seperated in day, month and year
 */
struct date{
	int day;
	int month;
	int year;
};

struct person{
	char *first_name, *last_name, *town;
	struct date date;
};

/*
 * This compares two structs and acts as the "<"-relation
 * p1 < p2 iff (p1->last_name < p2-last_name) or (p1->last_name = p2-last_name and p1->first_name < p2-first_name)
 */
int name_is_smaller(struct node* p1, struct node* p2);

int town_is_smaller(struct person* p1, struct person* p2);

int birthdate_is_smaller(struct person* p1, struct person* p2);

/*
 *Frees the memory allocated for the node, including all the memory allocated for the first_name, last_name.
 */
void free_struct_person(struct person*);



















#endif
