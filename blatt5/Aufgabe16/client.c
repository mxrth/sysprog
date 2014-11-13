/*Client:*/

#include <sys/types.h>
#include <sys/socket.h>

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
	char *hostname = /*Hostname muss eingefügt werden */
	/*Serveradresse */
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(80);
	dest.sin_addr.s_addr = get_in_addr(hostname);
	
	/*Länge der Adressstruktur */
	socklen_t addrlen; /*bestimmung addrlen */
	
	/*Socketerstellung*/
	sock = socket(AF_INET, SOCK_STREAM, 0);
		if(sock < 0){
			ERROR("Wasn't able to call function socket")	
		}
		
	/*Socket connect */	
	int connect(sock, &dest, addrlen);
	
	
	write()
	read()
	close()
	
	return 0;
}