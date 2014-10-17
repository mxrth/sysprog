#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mystring.h"

struct node* new_node(){
	struct node *new_pointer = malloc(sizeof(struct node));
	new_pointer->succ=NULL;
	return new_pointer;
}

void free_node(struct node* node){
	free(node->last_name);
	free(node->first_name);
	free(node);
	return;
}

void free_list(struct node* list){
    struct node *succ;
    while(list != NULL) {
	succ = list->succ;
	free_node(list);
	list = succ;
    }
}

/* < */
int is_smaller(struct node* p1, struct node* p2) {
	if(compare_strings(p1->last_name, p2->last_name) == Smaller) return 1;
	if(compare_strings(p1->last_name, p2->last_name) == Equal && compare_strings(p1->first_name, p2->first_name) == Smaller) return 1;
	return 0;
}

struct node * insert_sorted(struct node* list, struct node* new_entry){
	struct node* temp = list;
	/*
	If the list is empty, insert the new element at the beginning
	*/
	if(list==NULL){
		list=new_entry;
		return list;
	}
	/*
	Otherwise run through the list
	*/
	if(is_smaller(new_entry,temp)){
		new_entry->succ = temp;
		list = new_entry;
		return list;
	}
	for(;temp->succ!=NULL;temp=temp->succ){
		if(is_smaller(new_entry,temp->succ)){
			new_entry->succ=temp->succ;
			temp->succ=new_entry;
			return list;
		}
	}
	temp->succ=new_entry;
	return list;
}

/*
int main(){
	struct node* a1 = new_node();
	struct node* a2 = new_node();
	struct node* a3 = new_node();
	if(a1==NULL || a2 == NULL || a3 ==NULL){
		printf("ERROR");
		return EXIT_FAILURE;
	}
	a1->last_name = malloc(100*sizeof(char));
	a1->first_name = malloc(100*sizeof(char));
	a2->last_name = malloc(100*sizeof(char));
	a2->first_name = malloc(100*sizeof(char));
	a3->last_name = malloc(100*sizeof(char));
	a3->first_name = malloc(100*sizeof(char));
	struct node* list = NULL;
	
	a1->*(last_name) = "Hallo";
	a1->*(first_name) = "Hallo";
	a2->*(last_name) = "Hallo";
	a2->*(first_name) = "Hallo";
	a3->*(last_name) = "Hallo";
	a3->*(first_name) = "Hallo";
	
	list = 
} */
