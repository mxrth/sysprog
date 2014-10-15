#ifndef __h_mystring__
#define __h_mystring__

enum Ordering {
	Greater,
	Equal,
	Smaller
};

/*
 * Compares two strings lexically.
 * If a is greater than b it returns Greater
 * If a is equal to b it returns Equal
 * If a is smaller than b it returns Smaller
 * If a is a prefix of b and not equal to b, a is considered smaller
 * The empty string is smaller than all other strings.
 */
enum Ordering compare_strings(const char* a, const char* b);

/*
 * Returns a pointer to the first occurrence of `needle` in `haystack`, NULL if it is not present.
 */
char *find_char(const char * haystack, char needle);







#endif

