#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

#include "util.h"
#include "sockettools.h"
#include "bankclient.h"

int main(int argc, char* argv[]){
	int new_socket;
	int err;
	struct sockaddr_in serv_addr;
	
	get_address(&serv_addr);
	
	new_socket = prepare_socket_tcp();
	if(new_socket < 0){
		ERROR("Could not prepare the socket.")
	}

	printf("Trying to connect to server\n");
	err = connect(new_socket,(struct sockaddr*) &serv_addr,sizeof(serv_addr));
	if(err < 0){
		ERROR("Could not connect to server.")
	}
	
	handle_connection(new_socket);

	return 0;
}
