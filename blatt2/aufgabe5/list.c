#include <stdio.h>
#include <stdlib.h>
#include "list.h"

List new_node(){
	List new_pointer = malloc(sizeof(*new_pointer));
	if(new_pointer==NULL){
		return NULL;
	}
	new_pointer->succ=NULL;
	return new_pointer;
}

List insert_sorted(List list, void* new_data, int (*is_smaller)(void*, void*)){
	List temp = list;
	List new = new_node();
	if(new == NULL){
		return NULL;
	}
	new->data = new_data;
	
	/*
	If the list is empty, insert the new element at the beginning
	*/
	if(list==NULL){
		list=new;
		return list;
	}
	
	/*If new_entry is smaller than the first entry, modify the list-pointer*/
	if((*is_smaller)(new->data,temp->data)){
		new->succ = temp;
		list = new;
		return list;
	}
	
	/*
	Otherwise run through the list and insert at the correct position
	The node will be inserted at the first position where is_smaller returns 0
	This also handles the case of duplicate entries: the new one will be inserted after the last duplicate
	*/
	for(;temp->succ!=NULL;temp=temp->succ){
		if((*is_smaller)(new->data,temp->succ->data)){
			new->succ=temp->succ;
			temp->succ=new;
			return list;
		}
	}
	
	/*If the first steps fail the new entry has to be inserted at the end of the list*/
	temp->succ=new;
	
	return list;
}

/*For output of the list in the console*/
void print_list(List list, void (*print_entry(void*))){
    List temp = list;
	for(;temp != NULL;temp = temp->succ) {
		(*print_entry)(temp->data);
    }
	return;
}

void free_list(List list, void (*free_node)(void*)){
    List succ;
    while(list != NULL) {
		succ = list->succ;
		(*free_node)(list->data);
		free(list);
		list = succ;
    }
}



