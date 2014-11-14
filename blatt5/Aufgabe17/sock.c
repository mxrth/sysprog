#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "sock.h"
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

	/*Setting socket into passive mode*/
	err = listen(*tcp_sock, 5);
	
	if(err < 0){
		return -3;	
	}


	return 0;

}

int close_socket(int sock)
{
	return close(sock);
}


int manage_connections(int anzverbindungen,int tcp_sock, int (*managerfunction) (FILE * datastream, char *information))
{
	int handeled_connections = 0;
	int new_sock;
	struct sockaddr_in client_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);	

	while(anzverbindungen != 0){
		new_sock = accept(tcp_sock,(struct sockaddr*) &client_addr, &addrlen);
	
		if(new_sock<0){
			return -1;
		}

		printf("Recieved connection from %s!\n", inet_ntoa(client_addr.sin_addr));
		printf("A new socket was created!");
		print_port(new_sock);
	
		anzverbindungen--;
		handeled_connections++;
	}
	return handeled_connections;
}

int print_port(int sock) {
    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);
    if(getsockname(sock, (struct sockaddr*) &addr, &size) < 0 || sizeof(addr) < size) return -1; 
    printf("This socket has port %d\n", ntohs(addr.sin_port));
    return 0;
}


