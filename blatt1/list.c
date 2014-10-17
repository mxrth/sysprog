#include <stdlib.h>
#include "list.h"
#include "mystring.h"

struct node* new_node(){
	struct node *new_pointer = malloc(sizeof(struct node));
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
	for(;temp!=NULL;temp=temp->succ){
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
	free(temp);
	return list;
}
