#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mystring.h"

struct node* new_node(){
	struct node *new_pointer = malloc(sizeof(struct node));
	new_pointer->succ==NULL;
	return new_pointer;
}

void free_node(struct node* node){
	free(node->last_name);
	free(node->first_name);
	free(node);
	return;
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
	for(;temp->succ!=NULL;temp=temp->succ){
		if(compare_strings(new_entry->last_name,temp->succ->last_name)==Greater){
			continue;
		}
		if(compare_strings(new_entry->last_name,temp->succ->last_name)==Equal){
			if(compare_strings(new_entry->first_name,temp->succ->last_name)==Greater){
				continue;
			}
			if(compare_strings(new_entry->first_name,temp->succ->first_name)==Smaller||compare_strings(new_entry->first_name,temp->succ->first_name)==Equal){
				new_entry->succ=temp->succ;
				temp->succ=new_entry;
				break;
			}
		}
		if(compare_strings(new_entry->last_name,temp->succ->last_name)==Smaller){
			new_entry->succ = temp->succ;
			temp->succ=new_entry;
			break;
		}
	}
	temp->succ=new_node;
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
	a1->*(last_name) = "Hallo";
	a1->*(last_name) = "Hallo";
	a1->*(last_name) = "Hallo";
	a1->*(last_name) = "Hallo";
	a1->*(last_name) = "Hallo";
} */
