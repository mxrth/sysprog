#ifndef __h_mystring__
#define __h_mystring__

#include <stddef.h>
  enum Ordering
{ Greater, Equal, Smaller 
};
 
/*
 * Compares two strings lexically.
 * If a is greater than b it returns Greater
 * If a is equal to b it returns Equal
 * If a is smaller than b it returns Smaller
 * If a is a prefix of b and not equal to b, a is considered smaller
 * The empty string is smaller than all other strings.
 */ 
enum Ordering compare_strings (const char *a, const char *b);
 
/* 
 * Calculates the length of a given char
 * Assumes it is null terminated
 */ 
  size_t string_len (const char *);
 
/*
 * Copys a null terminated string from src to dest, and makes sure that dest is not overflowed and null-terminated
 *
 * dest_size: number of chars dest can hold
 * returns number of chars copyed from src
 */ 
  size_t string_copy (const char *src, char *dest, size_t dest_size);
    
#endif /*  */
  
