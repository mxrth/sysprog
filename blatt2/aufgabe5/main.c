#include "input.h"
#include "list.h"
#include "person.h"

#include <stdlib.h>
#include <stdio.h>

#define ERROR(s) {fprintf(stderr, "%s", (s)); exit(EXIT_FAILURE);}

typedef int (*cmp_func)(struct person*, struct person*);


int main(void) {
    FILE* in_file;

    struct person* person;
    List list = NULL;
    int selection = 0, result;
	
    cmp_func funcs[3] = {&name_is_smaller, &town_is_smaller, &birthdate_is_smaller}; 
    cmp_func func;
    /*Open the text file specified by the user*/
    in_file = get_input_file(); 
    if(!in_file) ERROR("Could not open input file")

    printf("Please select sorting function by entering the corresponding number:\n");
    printf("(1) By Name\n(2) By Town\n(3) By Birthdate\n");
    result = scanf("%d", &selection);
    if(result < 1 || selection > 3 || selection < 1) ERROR("Invalid number");
    func = funcs[selection-1];
	
    while((person = read_name(in_file)) != NULL) {
		list = insert_sorted(list, person, func);
    }

	/*Print the sorted list of the names*/
    print_list(list, print_person);
	
	/*Clean up memory and close file*/
    free_list(list, &free_struct_person);
    fclose(in_file);

    return EXIT_SUCCESS;
}
