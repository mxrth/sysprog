#include "input.h"

/*
 * Need for:
 * string_len
 * string_copy
 */
#include "mystring.h"

/*
 * Needed for:
 * calloc
 * NULL
 */
#include <stdlib.h>

/*
 * Needed for:
 * fscanf
 * scanf
 * printf
 * fopen
 * FILE
 * EOF
 */
#include <stdio.h>

/*
 * Allocates space for num objects of type *dest and stores the resulting pointer to dest
 * Iff an error is encountered the statement after ALLOC_OR is executed
 * Use like this:
 * ALLOC_OR(person, 15) { 
 *  panic(); 
 *  error(); 
 *  fuck();
 * }
 */
#define ALLOC_OR(dest, num) if(!( (dest) = calloc(num, sizeof( *(dest) )) ))


/*
 * Makes the following assumptions:
 * - `file` is a valid file pointer
 * - Each line of `file` consists of a first name and a last name seperated by space (' ')
 *   - each name consists of (ASCII)-characters (lower and upper) as well as '-' and '_' ([a-Z-_])
 *   - each name is shorter than 100 `char`s
 *  Returns NULL if not enough data could be read or memory allocation failed
 */
struct node *read_name(FILE* file) {

    /* used _size (and not for example _len) suffix to make clear these variables should hold the size 
     * of the _buffer_ holding firstname/lastname not the length of the string */
    size_t firstname_size, lastname_size;
    char first_name[101], last_name[101];
    struct node* person;
    int result;

    /*scanning might yield suprising results when one of the assumptions is broken,
     * but should be safe in any case */
    result = fscanf(file, "%100s %100s", first_name, last_name);
    
    /*fscanf returns how many parameters were filled, or EOF on error*/
    if(result < 2 || result == EOF) return NULL;

    /*buffer must be one `char` bigger than the length of the string to hold the terminationg '\0'*/
    firstname_size = string_len(first_name)+1;
    lastname_size = string_len(last_name)+1;

    person = new_node();
    if(!person) return NULL;
    
    ALLOC_OR(person->first_name, firstname_size) return NULL;
    ALLOC_OR(person->last_name, lastname_size) return NULL;

    string_copy(first_name, person->first_name, firstname_size);
    string_copy(last_name, person->last_name, lastname_size);


    return person;
    
}

FILE *get_input_file(void) {
    char path[256]; 
    printf("Please input file name\n");
    scanf("%255s", path);
    return fopen(path, "r");
    /* Interesting sidenote: clang with -fsanitize=... found the possible bug when path was
     * declared with `char path[255] _even_ when entering fewer than 255 chars*/
}








