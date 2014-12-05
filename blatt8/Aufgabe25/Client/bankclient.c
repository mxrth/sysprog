#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <ctype.h>

#include "bankclient.h"
#include "util.h"

int handle_connection(int socket){
	int err;	
	char user_input[100];
	char buffer[100];

	/* @ Max, hier ist der von mir hinzugefügte Teil. Der Rest sollte also funktionieren */

	/*Get list of accounts from the server*/
		printf("Waiting for answer from server.\n");  		
		bzero(buffer,100);
  		err = read(socket,buffer,100);
		if(err <= 0){
	    	printf("Failure to read, probably the server wants to close.\n");
			err = close(socket);
			if(err == -1){
				ERROR("Could not close socket.");			
			}
			return 0;
		}
		printf("%s\n", buffer);
	/*Getting User input: the account (socket) they want to use */
	int i;
	printf("please enter here the number of the account you want to use\n");
	scanf("%d",&i);  

	/*send server the account number */
	sprintf(user_input, "%i\n",i);
	err = write(socket,user_input,strlen(user_input));
	if(err <= 0){
		printf("Failure to write, probably the server wants to close.\n");
		printf("Closing this session\n");
		err = close(socket);
		if(err == -1){
			ERROR("Could not close socket.");			
		}			
	}
	/*bis hier, jetzt folgt Bens Code */
	
	while(1){
		/*Get the answer from the server*/
		printf("Waiting for answer from server.\n");  		
		bzero(buffer,100);
  		err = read(socket,buffer,100);
		if(err <= 0){
	    	printf("Failure to read, probably the server wants to close.\n");
			err = close(socket);
			if(err == -1){
				ERROR("Could not close socket.");			
			}
			return 0;
		}
		printf("Answer from the server:\n%s\n", buffer);
		
		/*Getting user input*/
		while(1){
			err = handle_user_input(user_input);
			if(err == 0){
				printf("Closing this session\n");
				err = close(socket);
				if(err == -1){
					ERROR("Could not close socket.");			
				}
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
				err = close(socket);
				if(err == -1){
					ERROR("Could not close socket.");			
				}
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

	if(check_user_input(user_input) == 1){
		return 1;
	}
	else return -1;
}

/*Input: A string that is supposed to be in the format 'Command' 'Number'
*This function verifies if this is correct
*
*/
int check_user_input(char *user_input){
	int i,k;

	for(i=0;i<100;i++){
		if(isalpha(user_input[i])){
			continue;		
		}
		break;
	}
	if(i < 1) return -1;
	if(!isspace(user_input[i])){
		return -1;
	}
	for(k=i+1;k<100;k++){
		if(isdigit(user_input[k])){
			continue;
		}
		break;
	}
	if(k==i+1) return -1;
	if(user_input[k] == '\n'){return 1;}
	else return -1;	
}
