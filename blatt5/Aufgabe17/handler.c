#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"

int handle_get_request(FILE *datastream,char *first_line ,char *information){
	char not_supported[50];	
	
	if(NULL == strstr(first_line,"HTTP/1.1")){
		sprintf(not_supported, "HTTP/1.1 505 HTTP Version Not Supported\r\n");
		printf("%s",not_supported);
		fprintf(datastream, "%s", not_supported);
		return -1;
	}

	return 0;
}

int manager(FILE *datastream, char *information)
{
	char not_implemented[50];	

	char *first_line;
	first_line = malloc(200*sizeof(char));
	if(first_line == NULL){
		ERROR("Couldn't allocate memory");
	}

	/*char *fgets(char *s, int size, FILE *stream);*/
	
	first_line = fgets(first_line, 200, datastream);	
	
	printf("First line of request is:\n%s\n",first_line);
	
	/*char *strstr(const char *haystack, const char *needle);*/
	if(first_line == strstr(first_line,"GET")){
		handle_get_request(datastream, first_line, information);
	}
	else{
		sprintf(not_implemented, "HTTP/1.1 501 Not implemented\r\n");
		printf("%s",not_implemented);
		fprintf(datastream, "%s", not_implemented);
	}	
	
	free(first_line);
	return 0;
}

