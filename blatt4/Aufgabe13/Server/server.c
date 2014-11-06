#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>


int main(void) {
    int sock;
    if( (sock = sock_init()) < 0) {
	ERROR("Could not initialize socket, aborting!\n");
    }
    print_hostport(sock);

    while(true) {
	handle_message(sock);
    }
    return 0;
}

int sock_open() {
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) return sock;
    addr.sin_family = AF_INET;
    addr.sin_port = 0; //no htnos needed
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr*) addr, sizeof struct sockaddr_in) < 0) return -1;
    return sock;
}

void print_hostport(int socket) {
    struct sockaddr my_addr;
}
