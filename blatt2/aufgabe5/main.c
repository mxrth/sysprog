#include "input.h"
#include "list.h"
#include "person.h"

#include <stdlib.h>
#include <stdio.h>

#define ERROR(s) {fprintf(stderr, "%s", (s)); exit(EXIT_FAILURE);}

int main(void) {
    FILE* in_file;

    struct node* person;
	List list = NULL;
	
	/*Open the text file specified by the user*/
    in_file = get_input_file(); 
    if(!in_file) ERROR("Could not open input file")
	
	
    while((person = read_name(in_file)) != NULL) {
		list = insert_sorted(list, person);
    }

	/*Print the sorted list of the names*/
    print_list(list);
	
	/*Clean up memory and close file*/
    free_list(list);
    fclose(in_file);

    return EXIT_SUCCESS;
}
