#include "input.h"
#include "list.h"

#include <stdlib.h>

#define ERROR(s) {fprintf(stderr, "%s", (s)); exit(EXIT_FAILURE);}

int main(void) {
    FILE* in_file;

    struct node* person, *list = NULL;

    in_file = get_input_file(); 
    if(!in_file) ERROR("Could not open input file")

    while((person = read_name(in_file)) != NULL) {
	list = insert_sorted(list, person);
    }

    print_list(list);

    /*free_list(list);*/

    return EXIT_SUCCESS;
}
