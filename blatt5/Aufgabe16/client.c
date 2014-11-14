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

#include "unp_readline.h"


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
	char *hostname = "172.16.1.103"; /*Hostname muss eingefügt werden */
	/*Serveradresse */
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(2005);
	dest.sin_addr = (get_in_addr(hostname)); 
	printf(" was Max Funktion get_in_addr() zurückgibt: %s \n", inet_ntoa(dest.sin_addr));
	
	/*Test Ben */
	/*dest.sin_addr.s_addr = inet_addr((get_in_addr(hostname));*/
	
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
	
printf(" Ich bin verbunden \n");
	
	/*write() */

	ssize_t t;
	char write_buff[255]; /*füllen mit inhalt*/
	
	strcpy(write_buff,"hello, ben!\r\n");
	
	ssize_t count = strlen(write_buff)+1;
	t =	write(sock, write_buff, count); /*write_buff oder  &write_buff?*/
	
	/*Überprüfung ob write() korrekt ausgeführt wurde */

	if(t < 0){
		ERROR("Wasn't able to write anything")	
	}
	if(t < count){
		ERROR("Wasn't able to write everything")	
	}	
	
printf(" Write wurde korrekt ausgeführt \n");
	
	/* read() */
	char read_buff[255]; /*wieviel Platz ist notwendig? */
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