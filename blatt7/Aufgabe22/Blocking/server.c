#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "unp_readline.h"

#include <netdb.h>

#include "util.h"

int sock_init(void);
int print_port(int);
void handle_stdin(int, struct sockaddr_in *dest);
void handle_remote(int);
int read_destination(struct sockaddr_in *dest);
struct in_addr get_in_addr(char* hostname);

int main(int argc, char* argv[]) {
    int sock;
    
    int stdin_first;
    struct sockaddr_in dest;

    if(argc < 2) ERROR("Usage: chat [send|receive]");
    
    if(argv[1][0] == 's') stdin_first = 1;
    else stdin_first = 0;

    if( (sock = sock_init()) < 0) {
	ERROR("Could not initialize socket, aborting!\n");
    }

    if(!print_port(sock)) ERROR("Cannot determine listening port!\n");
    
    read_destination(&dest);
    
    if(stdin_first) {
	while(1) {
	    handle_stdin(sock, &dest);
	    handle_remote(sock);
	}
    } else {
	while(1) {
	    handle_remote(sock);
	    handle_stdin(sock, &dest);
	}
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

void handle_remote(int sock) {
    ssize_t result;
    char buff[256] = {0};
    size_t len = 255;
    struct sockaddr_in addr;
    socklen_t addr_len;
    result = recvfrom(sock, buff, len, 0, (struct sockaddr*) &addr, &addr_len);
    if(result < 0) ERROR("recvfrom failed\n");
    //printf("Received message from %s:%d :\n", inet_ntoa(addr.sin_addr), ntohs(addr.sin_port));
    printf("%s", buff);
}

void handle_stdin(int sock, struct sockaddr_in *dest_addr) {
    ssize_t read;
    char buff[255] = {0};
    ssize_t err;
    printf("> "); fflush(stdout); 
    read = readline(STDIN_FILENO, buff, 254);
    if(read <= 0) {
	printf("Reading from stdin failed\n");
	return;
    }

    err = sendto(sock, buff, strlen(buff), 0, (struct sockaddr*) dest_addr, sizeof(struct sockaddr_in));

    if(err < 0){
	ERROR("Was not able to send message.")
    }
    
}

int read_destination(struct sockaddr_in *dest) {
    char buff[255] = {0},  hostname[255] = {0};
    unsigned port;



    printf("Please input a host port combination\n");
    readline(STDIN_FILENO, buff, 254);
    sscanf(buff, "%s %u", hostname, &port);
    printf("Sending to %s:%u\n", hostname, port);
    dest->sin_family = AF_INET;
    dest->sin_port = htons(port);
    
    dest->sin_addr = get_in_addr(hostname);
    return 1;
}

struct in_addr get_in_addr(char* hostname) {
    int err;
    struct in_addr addr;
    struct addrinfo *addr_res, hints = {0};
    hints.ai_family = AF_INET;
    err = getaddrinfo(hostname, NULL, &hints, &addr_res);
    if(err != 0) {ERROR("Could not resolve hostname")}
    /*only using the first list entry*/
    addr = ( (struct sockaddr_in *) addr_res->ai_addr)->sin_addr;
    freeaddrinfo(addr_res);
    return addr;
}

