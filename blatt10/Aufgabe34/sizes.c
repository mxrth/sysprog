#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void) {
    printf("sizeof(sa_family_t) == %#lx\n", sizeof(sa_family_t));
    printf("sizeof(in_port_t) == %#lx\n", sizeof(in_port_t));
    printf("sizeof(struct in_addr) == %#lx\n", sizeof(struct in_addr));
    printf("sizeof(struct sockaddr_in) == %#lx\n", sizeof(struct sockaddr_in));
    printf("AF_INET == %#lx\n", AF_INET);
}
