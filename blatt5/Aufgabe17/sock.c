#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include "util.h"

int prepare_socket(int portnum, int *tcp_sock)
{
	int err;
	struct sockaddr_in myaddr;

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(portnum);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	*tcp_sock = socket(AF_INET,SOCK_STREAM,0);
	
	if(*tcp_sock < 0){
		return -1;
	}

	err = bind(*tcp_sock, (struct sockaddr*) &myaddr, sizeof(struct sockaddr_in));
	
	if(err < 0){
		return -2;	
	}


	return 0;

}

int close_socket(int sock)
{
	return close(sock);
}

/*
int manage_connections(int anzverbindungen, int (*managerfunction) (FILE * datastream, char *information))
{
	// ...
}*/

int print_port(int sock) {
    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);
    if(getsockname(sock, (struct sockaddr*) &addr, &size) < 0 || sizeof(addr) < size) return -1; 
    printf("Listening on port %d\n", ntohs(addr.sin_port));
    return 0;
}


