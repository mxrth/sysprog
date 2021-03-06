#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "mystring.h"
 int is_smaller (struct node *p1, struct node *p2);
 struct node *
new_node ()
{
  struct node *new_pointer = malloc (sizeof (struct node));
  new_pointer->succ = NULL;
  return new_pointer;
}

 void
free_node (struct node *node)
{
  free (node->last_name);
  free (node->first_name);
  free (node);
  return;
}

 void
free_list (struct node *list)
{
  struct node *succ;
  while (list != NULL)
    {
      succ = list->succ;
      free_node (list);
      list = succ;
    }
}

 
/* < */ 
  int
is_smaller (struct node *p1, struct node *p2)
{
  
    /*Compare first names */ 
    if (compare_strings (p1->last_name, p2->last_name) == Smaller)
    return 1;
  
    /*If the first names are equal compare the last names */ 
    if (compare_strings (p1->last_name, p2->last_name) == Equal 
	&&compare_strings (p1->first_name, p2->first_name) == Smaller)
    return 1;
  return 0;
}

 struct node *
insert_sorted (struct node *list, struct node *new_entry)
{
  struct node *temp = list;
  
    /*
       If the list is empty, insert the new element at the beginning
     */ 
    if (list == NULL)
    {
      list = new_entry;
      return list;
    }
   
    /*If new_entry is smaller than the first entry, modify the list-pointer */ 
    if (is_smaller (new_entry, temp))
    {
      new_entry->succ = temp;
      list = new_entry;
      return list;
    }
   
    /*
       Otherwise run through the list and insert at the correct position
       The node will be inserted at the first position where is_smaller returns 0
       This also handles the case of duplicate entries: the new one will be inserted after the last duplicate
     */ 
    for (; temp->succ != NULL; temp = temp->succ)
    {
      if (is_smaller (new_entry, temp->succ))
	{
	  new_entry->succ = temp->succ;
	  temp->succ = new_entry;
	  return list;
	}
    }
   
    /*If the first steps fail the new entry has to be inserted at the end of the list */ 
    temp->succ = new_entry;
   return list;
}

 
