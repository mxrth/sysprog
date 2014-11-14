#include <stdio.h>
#include <stdlib.h>

#include "util.h"

int manager(FILE *datastream, char *information)
{
	char *first_line;
	first_line = malloc(200*sizeof(char));
	if(first_line == NULL){
		ERROR("Couldn't allocate memory");
	}
	
	/*char *fgets(char *s, int size, FILE *stream);*/
	
	first_line = fgets(first_line, 200, datastream);	
	
	printf("First line of request is:\n%s\n",first_line);

	return 0;
}

/*
int handle_get_request(FILE *datastream, char *information){


	return 0;
}
*/
