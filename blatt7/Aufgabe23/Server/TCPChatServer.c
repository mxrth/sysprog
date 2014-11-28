
#include <sys/select.h>
#include <sys/time.h>


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

int main() {


	/*prepare listening sockets ? */
	
	int sock;
	err = prepare_socket(4711, &sock);
	if(err < 0){
		ERROR(Couldn't prepare socket);	
	}



	/* look for and handle incoming connections */

	/*select loop with reading and sending messages */

	/*closing sockets for diconnected clients */






	return 0;
}
