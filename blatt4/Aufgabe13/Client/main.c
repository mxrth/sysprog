#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

#include "input.h"
#include "util.h"

int main(int argc, char* argv[]){
	int sock, err;
	/*struct sockaddr_in addr;*/
	struct sockaddr_in dest;
	char message[256];

	if(argc < 2){
		ERROR("Not the right amount of input parameters.\n Use like this: ./client 'Hostname' 'Portname'")
	}

	dest.sin_family = AF_INET;
	dest.sin_port = htons(atoi(argv[2]));
	dest.sin_addr.s_addr = inet_addr(argv[1]);

	printf("Sending to server %s to port %s\n",argv[2],argv[1]);
	
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(sock < 0){
		ERROR("Wasn't able to call function socket")	
	}
	
	/*
	addr.sin_family = AF_INET;
	addr.sin_port = htons(4711);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	

	err = bind(socket, (struct sockaddr *) &addr,sizeof(struct sockaddr_in));

	if(err < 0){
		ERROR("Problem while binding socket")
	}
	*/

	printf("Type your message to send to server. Type 'q' to quit\n");

	while(1){
		get_input_console (message);		
		err=sendto(sock, message, strlen(message) + 1, 0, (struct sockaddr*) &dest, sizeof(struct sockaddr_in));
		if(err < 0){
			ERROR("Was not able to send message. Please try again.")
		}
	}
	
	if(close(sock)<0){
		ERROR("Could not close the socket")
	}

	return 0;
}	
