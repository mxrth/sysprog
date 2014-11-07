#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>


#include "util.h"

int main(int argc, char* argv[]){
	int socket;
	struct sockaddr_in addr;
	
	if(argc < 2){
		ERROR("Not the right amount of input parameters.\n Use like this: ./client 'Hostname' 'Portname'")
	}
	
	socket = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(socket < 0){
		ERROR("Wasn't able to call function socket")	
	}

	addr.sin_family = AF_INET;
	addr.sin_port = htons(4711);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	err = bind(socket, (struct sockaddr *) &addr,sizeof(struct sockaddr_in));

	if(err < 0){
		ERROR("Problem while binding socket")
	}

	



	



	return 0;
}	
