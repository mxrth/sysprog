
#include <stdio.h>
#include "mystring.h"


/*
 * Compares two strings lexically.
 * If a is greater than b it returns Greater
 * If a is equal to b it returns Equal
 * If a is smaller than b it returns Smaller
 * If a is a prefix of b and not equal to b, a is considered smaller
 * The empty string is smaller than all other strings.
 */
enum Ordering compare_strings(const char* a, const char* b) {
	int i = 0;
	while(1){
		/*tests if one of the strings is empty*/
		if(*(a+i) == '\0') {
			if(*(b+i) =='\0') {
				return Equal;
			}
			return Smaller;
		}
		if(*(b+i) =='\0') {
			return Greater;
		}
		if(*(a+i)<*(b+i)){
			return Smaller;
		}
		if(*(a+i)>*(b+i)){
			return Greater;
		}
		if(*(a+i) == *(b+i)){
			i++;
		}
	}
}

/*
 * Returns a pointer to the first occurrence of `needle` in `haystack`, NULL if it is not present.
 */
char *find_char(const char * haystack, char needle) {
	char *cursor = haystack;
	while(*cursor != needle) {
		cursor++;
		if(*cursor == '\0') {
			return NULL;
		}
	}
	return cursor;
}
