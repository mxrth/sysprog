#include "list.h"

#include <stdlib.h>
#include <stdio.h>

/*For output of the list in the console*/
void print_list(const struct node* person) {
    for(;person != NULL;person = person->succ) {
	printf("%s %s\n", person->first_name, person->last_name);
    }
}
