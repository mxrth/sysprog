/*Client:*/

#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "util.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


/*Von Aufgabe 12 */
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

int main() {

	/*Hostname */
	char *hostname = ""; /*Hostname muss eingefügt werden */
	/*Serveradresse */
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(80);
	dest.sin_addr.s_addr = *inet_ntoa(get_in_addr(hostname));
	
	/*Länge der Adressstruktur */
	/*socklen_t addrlen; --bestimmung addrlen */
	
	/*Socketerstellung*/
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0){
		ERROR("Wasn't able to call function socket")	
	}
		
	/*Socket connect */	
	int c;
	c = connect(sock, (struct sockaddr *)&dest, sizeof(dest));
	if(c < 0){
			ERROR("Wasn't able to call function connect")	
		}
		
	/*write() */

	ssize_t t;
	char write_buff[]; /*füllen mit inhalt*/
	ssize_t count = strlen(write_buff)+1;
	t =	write(sock, write_buff, count); /*write_buff oder  &write_buff?*/
	
	/*Überprüfung ob write() korrekt ausgeführt wurde */
	if(t < 0){
		ERROR("Wasn't able to write anything")	
	}
	if(t < count){
		ERROR("Wasn't able to write everything")	
	}	
	
	/* read() */
	char read_buff[]; /*wieviel Platz ist notwendig? */
	ssize_t r;
	r = read(sock, read_buff, strlen(read_buff)+1); /*FileDescriptor vom richtigen Socket?)*/
	
	/*Fehlerabfangen */
	if(r < 0){
		ERROR("Wasn't able to read")	
	}
	/* =0 Verbindungsabbau */
	
	/*close*/
	int clos;
	clos = close(sock);
	if(clos < 0){
			ERROR("Wasn't able to close the socket")	
		}
	
	return 0;
}