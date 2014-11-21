#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include "bankclient.h"

int handle_connection(int socket){
	int err;	
	char user_input[100];
	char buffer[100];
	while(1){
		/*Get the answer from the server*/
		printf("Waiting for answer from server.\n");  		
		bzero(buffer,100);
  		err = read(socket,buffer,100);
		if(err <= 0){
	    	printf("Failure to read, probably the server wants to close.\n");
			close(socket);
			return 0;
		}
		printf("Answer from the server:\n%s\n", buffer);
		
		/*Getting user input*/
		while(1){
			err = handle_user_input(user_input);
			if(err == 0){
				printf("Closing this session\n");
				close(socket);
				return 0;
			}
			if(err == -1){
				printf("Error while getting user input. Please try again or quit.\n");
				continue;
			}
			/*Send command to the server*/
			printf("Sending command '%s' to the server\n", user_input);
			err = write(socket,user_input,strlen(user_input));
	  		if(err <= 0){
				printf("Failure to write, probably the server wants to close.\n");
				printf("Closing this session\n");
				close(socket);
				return 0;
			}
			break;
		}
	}	
	return 0;
}

/*Return -1 on error
*		0 if the user wants to quit
*		1 on success
*
*/
int handle_user_input(char *user_input){
	char* err;
	printf("Please use one of the following functions:\n");
	printf("Deposit 'amount'\n");
	printf("Withdraw 'amount'\n");
	printf("Quit\n");
	
	err = fgets(user_input, 100, stdin);
	if(err == NULL){
		return -1;
	}

	if(user_input[0] == 'Q'){
		return 0;
	}	
	
	return 1;
}
