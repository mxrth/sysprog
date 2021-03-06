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
    /*after the loop dest points one past the last copied char*/
    *dest = '\0';
    return copied;
}

size_t string_len(const char *str) {
    size_t len = 0;
    for(;*str != '\0'; str++, len++);
    return len;
}


