#include "input.h"
#include "assert.h"
/*FIXME: Reimplement strlen*/
#include <string.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 100
/*the additional chars are for linefeed*/
#define BUFF_SIZE (MAX_NAME_SIZE * 2 + 2)

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
 * Copys a null terminated string from src to dest, and makes sure that dest is not overflowed and null-terminated
 *
 * dest_size: number of chars dest can hold
 */
string_copy(const char* src, char* dest, size_t dest_size) {
    
}

struct node *read_name(FILE* fp) {
    char buff[BUFF_SIZE];
    char *space;

    size_t firstname_size, lastname_size;
    
    struct node* person;
    char* first_name, *last_name;

    if(fgets(buff, sizeof(buff), fp) == NULL) {
	return NULL;
    }

    space = find_char(buff, ' ');
    
    assert(space != NULL && "Expected input format: `Firstname<space>Lastname<linebreak>");
    
    /*Off by ones ahead!*/
    /*
     * 0123456789
     * firs last0
     */
    *space = '\0';
     
     /*
      * 0123456789
      * firs0last0
      * Also count the terminating NUL byte
      */
    firstname_size = strlen(buff)+1;
    lastname_size = strlen(space+1)+1;
    
    /* allocate some stuff */
    person = new_node();
    if(!person) return NULL;
    
    ALLOC_OR(first_name, firstname_size) return NULL;
    ALLOC_OR(last_name, lastname_size) return NULL;

    string_copy(buff, first_name, firstname_size);
    string_copy(space+1, last_name, lastname_size);

    person->first_name = first_name;
    person->last_name = last_name;

    return person;
    
}
