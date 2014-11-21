#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util.h"
#include <stdarg.h>

#define ERR_OK 0
#define ERR_BAD_VERSION 1
#define ERR_NO_HOST 2
#define ERR_REQ_TOO_LONG 3

#define MAX_URI_LEN  255 
#define MAX_LINE (MAX_URI_LEN + 50)

/*Helper function to write something to a stream as well as stdout*/
void print_log(FILE* stream, char* format, ...) {
    va_list ap;
    va_start(ap, format);
    vprintf(format, ap);
    va_end(ap);

    va_start(ap,format);
    vfprintf(stream, format, ap);
    va_end(ap);
}

int parse_get_request(const char* line, FILE* stream, char* res) {
    int i, found_host=0;
    char cur_line[MAX_LINE];
    line += 4; /*Skip 'GET '*/
    /*parse resource*/
    for(i = 0; i < MAX_URI_LEN && line[i] != ' '; i++) {
	res[i] = line[i];
    }
    if(line[i] != ' ') return ERR_REQ_TOO_LONG;

    /*Parse version and rest of request-header, looking out for Host*/
    if(strstr(&line[i] , "HTTP/1.1") == NULL) return ERR_BAD_VERSION;
    while(fgets(cur_line, MAX_LINE, stream) != NULL) {
	if(strstr(cur_line, "Host: ") != NULL) found_host = 1;
	if(found_host) printf("Found host\n");
	if(cur_line[0] == '\r' || cur_line[0] == '\n' ) break;
    }

    if(!found_host) return ERR_NO_HOST;
    return ERR_OK;
}


int handle_get_request(FILE *datastream,char *first_line ,char *information){
	
	char ressource[MAX_URI_LEN] = {0};
	
	int error = parse_get_request(first_line, datastream, ressource );
	
	if(error != 0) {
	    if(error == ERR_BAD_VERSION )
		print_log(datastream, "HTTP/1.1 505 HTTP Version Not Supported\r\n\r\n");
	    else if(error == ERR_NO_HOST)
		print_log(datastream, "HTTP/1.1 400 Bad Request\r\n\r\n");
	    else if(error == ERR_REQ_TOO_LONG)
		print_log(datastream, "HTTP/1.1 414 Request-URI Too Long\r\n\r\n");
	    return -1;
	}

	print_log(datastream, "HTTP/1.1 200 OK\r\n");
	print_log(datastream, "Conent-Type: text/plain\r\n");
	print_log(datastream, "\r\n");
	print_log(datastream, "Anfrage entgegengenommen\r\n");
	print_log(datastream, "Ressource: %s\r\n", ressource);
	print_log(datastream, "Client ID: %s\r\n", information);
	

	return 0;
}

int manager(FILE *datastream, char *information)
{

	char *first_line;
	first_line = malloc(MAX_LINE); //sizeof char == 1
	if(first_line == NULL){
		ERROR("Couldn't allocate memory");
	}

	first_line = fgets(first_line, MAX_LINE , datastream);	
	if(first_line == NULL) {
	    printf("Client closed connection?\n");
	    return 1;
	}
	
	printf("First line of request is:\n%s\n",first_line);
	
	/*Check if the first request line starts with GET*/
	if(first_line == strstr(first_line,"GET")){
		handle_get_request(datastream, first_line, information);
	}
	else{
		print_log(datastream, "HTTP/1.1 501 Not implemented\r\n\r\n");
	}	
	
	free(first_line);
	return 0;
}

