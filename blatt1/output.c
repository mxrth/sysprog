#include "list.h"

#include <stdlib.h>
#include <stdio.h>

void print_list(const struct node* person) {
    for(;person->succ != NULL;person = person->succ) {
	printf("%s %s\n", person->first_name, person->last_name);
    }
}
