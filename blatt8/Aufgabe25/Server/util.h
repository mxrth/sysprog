#ifndef UTIL_H
#define UTIL_H
#include <stdlib.h>
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

#define ERROR(s) {printf("ERROR:\n %s \n",s);exit(1);} 

#endif
