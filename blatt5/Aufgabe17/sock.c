#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "sock.h"
#include "util.h"

/*Input: A valid portnumber 'portnum', an int-pointer where the file descriptor of the new socket will be saved in 
 *
 *Output: Negative numbers are error codes:
 *
 *Upon success the file descripter of the new socket will be in the int 'tcp_sock'
 */
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
	FILE *datastream;	
	int handeled_connections = 0;
	int new_sock, err;
	struct sockaddr_in client_addr;
	socklen_t addrlen = sizeof(struct sockaddr_in);	
	
	/*Handle anzverbindungen connections*/
	while(anzverbindungen != 0){
		/*Accepting connections on the TCP-Socket*/		
		new_sock = accept(tcp_sock,(struct sockaddr*) &client_addr, &addrlen);
	
		if(new_sock<0){
			return -1;
		}

		printf("Recieved connection from %s!\n", inet_ntoa(client_addr.sin_addr));
		printf("A new socket was created!\n");
	
		/*Creating a stream on the new socked with fdopen*/
		datastream = fdopen(new_sock, "r+");
		if(datastream == NULL){
			return -2;		
		}
		
		/*Calling the managerfunction on the stream created by fdopen*/
		(*managerfunction)(datastream, inet_ntoa(client_addr.sin_addr));
		
		/*Closing the stream*/
		err = fclose(datastream);
		if(err == EOF){
			printf("ERROR! Couldn't close stream\n\n");
		}
		
		/*Adjusting iterators*/
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


