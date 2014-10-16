#include "input.h"
#include "assert.h"

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
#define ALLOC_OR(dest, num) if(!( (dest) = calloc(num, sizeof( *(dest) )) )

/*
 * Copys a null terminated string from src to dest, and makes sure that dest is not overflowed and null-terminated
 *
 * dest_size: number of chars dest can hold
 * returns number of chars copyed from src
 */
size_t string_copy(const char* src, char* dest, size_t dest_size) {
    size_t copied = 0;
    const size_t copy_max = dest_size - 1; /*leave space for null byte*/
    while(*src != '\0' && copied < copy_max) {
	*dest = *src;
	src++; dest++;
	copied++;
    }
    /*after the while dest points one past the last copied char*/
    *dest = '\0';
    return copied;
}

struct node *read_name(FILE* fp) {
    char buff[BUFF_SIZE];
    char *space;

    size_t firstname_len, lastname_len;
    
    struct node* person;
    char* first_name, *last_name;

    if(fgets(buff, sizeof(buff), fp) == NULL) {
	return NULL;
    }

    space = find_char(buff, ' ');
    
    assert(space != NULL && "Expected input format: `Firstname<space>Lastname<linebreak`")
    
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

    str_copy(buf, first_name, firstname_size);
    str_copy(space+1, last_name, lastname_size);

    person.first_name = first_name;
    person.last_name = last_name;

    return person;
    
}
