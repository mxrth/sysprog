/*Client:*/

#include <sys/types.h>
#include <sys/socket.h>

int main() {
	sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0){
			ERROR("Wasn't able to call function socket")	
		}
		
	int connect(int sockfd, const struct sockaddr *serv_addr,
	socklen_t addrlen);
	write()
	read()
	close()
	
	return 0;
}