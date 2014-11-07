#include "util.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

int big_endian(void) {
    uint16_t test_bytes = 0xBEEF;
    uint8_t low_byte = *( (uint8_t *) &test_bytes);
    if(low_byte == 0xBE) return 1;
    else return 0;
}

char* my_inet_ntoa(struct in_addr in) {
    static char addr_str[16];
    uint8_t bytes[4];
    uint32_t addr = * ( (uint32_t *) &in.s_addr );
    for(int i = 0; i < 4; i++) {
	int index = big_endian() ? 3-i : i;
	bytes[index] = (addr & (0xFF << i*8)) >> i*8;
    }
    snprintf(addr_str, 16, "%d.%d.%d.%d", bytes[0], bytes[1], bytes[2], bytes[3]);
    return addr_str;
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

int main(int argc, char* argv[]) {
    struct in_addr addr;
    if(argc < 2) ERROR("Not enough arguments");
    if(big_endian()) printf("Big endian!\n");
    else printf("Little endian!\n");
    addr = get_in_addr(argv[1]);
    printf("IP-Address according to inet_ntoa:    %s\n", inet_ntoa(addr));
    printf("IP-Address according to my_inet_ntoa: %s\n", my_inet_ntoa(addr));
}

