#ifndef _INPUT_H
#define _INPUT_H

#include <stdio.h>
#include "mystring.h"
#include "list.h"

/*
 * Reads a line from the given FILE pointer
 * and tries to split it at the first occurrence of a space character (" ") into first and last name
 * and writes them into a newly allocated node struct.
 * If no space is present the line is interpreted as first name, last name is left empty (one NUL byte).
 * First and last name are allocated on the heap (just like the struct)
 * Returns a pointer to the newly allocated node, NULL on failure
 */
struct node *read_name(FILE* in);

/*
 * Tries to read a filename from stdin an opens the file.
 * Returns a file handle on success, NULL otherwise
 */
FILE* get_input_file();



#endif

