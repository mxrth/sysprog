#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "socket.h"

int get_address(struct sockaddr_in *server_address){
	int n_items, portnumber_temp;
	int err;
	char user_input[100];
	char server_ip[100];	

	server_address -> sin_family = AF_INET;		

	/*Get the ip of the server to connect to as user input*/
	do{
		printf("Please enter the server ip of the bank:\n");
		fgets(user_input, 100, stdin);
		err = sscanf(user_input,"%s", server_ip);
	} while(err == 0);
	printf("You entered the ip-address %s\n", server_ip);
	server_address->sin_addr.s_addr = inet_addr(server_ip);
	
	/*Get the port of the server to connect to as user input*/
	n_items = 0;
	do{
		printf("Please enter the portnumber:\n");
		fgets(user_input, 100, stdin);
		err = sscanf(user_input,"%d", &portnumber_temp);
	} while(err == 0);
	printf("You set the portnumber to %i\n", portnumber_temp);
	server_address->sin_port = htons(portnumber_temp);

	return 0;
}

int prepare_socket_tcp(){
	int socknumber;
		
	socknumber = socket(AF_INET, SOCK_STREAM, 0);
	if(socknumber < 0){
		return -1;
	}	
	
	return socknumber;
}
