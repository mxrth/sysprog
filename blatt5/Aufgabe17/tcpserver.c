#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "sock.h"
#include "handler.h"
#include "util.h"

/*Input: Parameter 1 is the number of requests that should be handeled
 *	 Parameter 2 is the port number on which the server should run (use >1024)
 *
 */
int main(int argc, char **argv)
{
	int anzverbindungen;
	int portnumber;
	int tcp_sock;
	int err;


	if(argc <3){
		ERROR("Not the right amount of input parameters\n Use like this: ./tcpserver 'Number of requests' 'Portnumber'")
	}

	anzverbindungen = atoi(argv[1]);
	portnumber = atoi(argv[2]);

	if(anzverbindungen < 0 || portnumber < 0){
		ERROR("Invalid input")	
	}

	printf("Server is going to handle %i requests on port %i\n", anzverbindungen, portnumber);

	err = prepare_socket(portnumber, &tcp_sock);
	
	if (err == -1) {
		ERROR("Could not create socket\n")
		return 1;
	}
	if (err == -2) {
		ERROR("Could not bind socket\n")
		return 1;
	}
	if (err == -3) {
		ERROR("Could not put socket into listening mode\n")
		return 1;
	}

	print_port(tcp_sock);

	anzverbindungen = manage_connections(anzverbindungen,tcp_sock, 	&manager);
	if(anzverbindungen == -2){
		ERROR("Could not open stream mit fdopen.")
	}
	if(anzverbindungen == EOF){
		ERROR("Could not close stream.")
	}
	
	printf("%d Verbindungen wurden behandelt.\n", anzverbindungen);
	
	err = close_socket(tcp_sock);

	if(err < 0){
		ERROR("Couldn't close socket")
	}

	return 0;
}
