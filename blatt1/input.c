#include "input.h"
#include "mystring.h"
#include <assert.h>
/*FIXME: Reimplement strlen*/
#include <string.h>
#include <stdlib.h>
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

size_t string_len(const char *str) {
    size_t len = 0;
    for(;*str != '\0'; str++, len++);
    return len;
}

struct node *read_name(FILE* fp) {

    size_t firstname_size, lastname_size;
    
    struct node* person;
    char first_name[101], last_name[101];
    
    int result;

    result = fscanf(fp, "%100s %100s", first_name, last_name);
    
    if(result < 2 || result == EOF) return NULL;

    firstname_size = string_len(first_name);
    lastname_size = string_len(last_name);
    
    /* allocate some stuff */
    person = new_node();
    if(!person) return NULL;
    
    ALLOC_OR(person->first_name, firstname_size) return NULL;
    ALLOC_OR(person->last_name, lastname_size) return NULL;

    string_copy(last_name, person->first_name, firstname_size);
    string_copy(first_name, person->last_name, lastname_size);


    return person;
    
}

FILE *get_input_file(void) {
    char path[255];
    printf("Please input file name");
    scanf("%255s", path);
    return fopen(path, "r");
}








