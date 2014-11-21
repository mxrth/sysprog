#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "socket.h"

int get_address(struct sockaddr *server_address){
	int n_items, portnumber_temp;	
	char server_ip[100];	

	server_address -> sin_family = AF_INET;		

	/*Get the ip of the server to connect to as user input*/
	printf("Please enter the server ip of the bank:\n");
	do{
		printf("Please enter the server ip of the bank:\n");
		n_items = scanf("%s", server_ip);
	} while(n_items == 0);
	server_address->sin_addr.s_addr = inet_addr(const char *dotted);	
	
	/*Get the port of the server to connect to as user input*/
	n_items = 0;
	do{
		printf("Please enter the portnumber:\n");
		n_items = scanf("%d", &portnumber_temp);
	} while(n_items == 0);
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
