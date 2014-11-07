#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "util.h"

int sock_init(void);
int print_port(int);
void handle_message(int);

int main(void) {
    int sock;
    if( (sock = sock_init()) < 0) {
	ERROR("Could not initialize socket, aborting!\n");
    }

    if(!print_port(sock)) ERROR("Cannot determine listening port!\n");
    
    while(1) {
	handle_message(sock);
    }
    return 0;
}

int sock_init() {
    int sock;
    struct sockaddr_in addr;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if(sock < 0) return sock;
    addr.sin_family = AF_INET;
    addr.sin_port = 0; //no htnos needed
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(sock, (struct sockaddr*) &addr, sizeof(struct sockaddr_in) ) < 0) return -1;
    return sock;
}

int print_port(int sock) {
    struct sockaddr_in addr;
    socklen_t size = sizeof(addr);
    if(getsockname(sock, (struct sockaddr*) &addr, &size) < 0 || sizeof(addr) < size) return 0; 
    printf("Listening on port %d\n", ntohs(addr.sin_port));
    return 1;
}

void handle_message(int sock) {
    ssize_t result;
    char buff[256] = {0};
    size_t len = 255;
    struct sockaddr_in addr;
    socklen_t addr_len;
    result = recvfrom(sock, buff, len, 0, (struct sockaddr*) &addr, &addr_len);
    if(result < 0) ERROR("recvfrom failed\n");
    printf("Received message from %s:%d :\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    printf("%s", buff);
    printf("\n");
}
