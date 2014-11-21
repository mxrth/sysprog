#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "util.h"
#include "sockettools.h"
#include "bankclient.h"

int main(int argc, char* argv[]){
	int new_socket;
	int err;
	struct sockaddr_in serv_addr;
	
	get_address(server_addr);
	
	new_socket = prepare_socket_tcp();
	if(new_socket < 0){
		ERROR("Could not prepare the socket.")
	}

	err = connect(new_socket,&serv_addr,sizeof(serv_addr));
	if(err < 0){
		ERROR("Could not connect to server.")
	}
	
		

	return 0;
}
