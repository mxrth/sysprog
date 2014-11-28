#include <stdio.h>
#include <sys/select.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "sockettools.h"
#include "util.h"

#define MAX_MESSAGE_LENGTH 255

int get_nickname(char* nickname){
    char user_input[30];
	
    printf("Please enter your nickname (max. 30 characters):\n");
	fgets(user_input,30,stdin);
    return sscanf(user_input, "%s", nickname);
}

int handle_connection(int socketfd, char* nickname){
    int res;
    /*a > b ? a : b returns the maximum*/    
    int max = socketfd > STDIN_FILENO ? socketfd : STDIN_FILENO;
    max++;
    fd_set rset;
    char buffer[MAX_MESSAGE_LENGTH];
	char formatted_str[MAX_MESSAGE_LENGTH + 60];
	struct sockaddr_in mysocket;
	mysocket = getsockname_wrapper(socketfd);
	/* The ip-address is inet_ntoa(mysocket.sin_addr)*/
    
    while(1){
        FD_ZERO(&rset);
        FD_SET(socketfd,&rset);
        FD_SET(STDIN_FILENO,&rset);
    
        res = select(max, &rset, NULL, NULL, NULL);
        if(res<=0){
            printf(">>> ERROR in the select function.\nThe programm will continue to run\n");
            continue;
        }
        
        /*There is a message from the server*/
        if(FD_ISSET(socketfd,&rset)){
            bzero(buffer, MAX_MESSAGE_LENGTH);             
            res = read(socketfd, buffer, MAX_MESSAGE_LENGTH);
			if(res < 0){
				printf(">>> Failure to read message from server\n");
			}
			if(res == 0){
				printf(">>> Read returned 0, closing connection to server\n");
				return 0;			
			}
			else{
				printf("%s",buffer);
			}
        }
        /*The user has made an input and the message has to be send to the server*/
        if(FD_ISSET(STDIN_FILENO,&rset)){
			bzero(buffer, MAX_MESSAGE_LENGTH);
			bzero(formatted_str, strlen(formatted_str)); 			
			fgets(buffer, MAX_MESSAGE_LENGTH, stdin);
			sprintf(formatted_str,"\x1B[34m%s\x1B[39m @ [\x1B[93m%s\x1B[39m] %s", nickname, inet_ntoa(mysocket.sin_addr), buffer);			
			res = write(socketfd,formatted_str,strlen(formatted_str));
			if(res<0){
				printf(">>> Write returned negativ value, your message wasn't send\n");			
			}			
			if(res == 0){
				printf(">>> Write returned 0, closing connection to server\n");
				return 0;			
			}
        }        
    }

    return 0;
}
