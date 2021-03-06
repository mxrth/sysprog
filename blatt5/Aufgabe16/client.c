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
	/*Max :char *hostname = "172.16.1.101"; *//*Hostname muss eingefügt werden */
	
	char *hostname = "net.cs.uni-bonn.de";
	
	
	/*Serveradresse */
	struct sockaddr_in dest;
	dest.sin_family = AF_INET;
	dest.sin_port = htons(80);
	dest.sin_addr = (get_in_addr(hostname)); 
	
	/*printf(" was Max Funktion get_in_addr() zurückgibt: %s \n", inet_ntoa(dest.sin_addr)); */
	
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
	
	printf(" Connected! \n");
	
	/*write() */

	ssize_t t;
	char write_buff[255];
	
	strcpy(write_buff,"GET /de/wg/cs/lehre/ws-201415/sysprog HTTP/1.1\r\nFrom: Gruppe42\r\nHost: net.cs.uni-bonn.de\r\n\r\n");
	
	ssize_t count = strlen(write_buff)+1;
	t =	write(sock, write_buff, count); /*write_buff oder  &write_buff?*/
	
	/*Überprüfung ob write() korrekt ausgeführt wurde */
	if(t < 0){
		ERROR("Wasn't able to write anything")	
	}
	if(t < count){
		ERROR("Wasn't able to write everything")	
	}	
	
	printf(" Get Anfrage geschickt \n\n");
	
	
	
	/* read() */

	
	char read_buff[MAXLINE]; /*wieviel Platz ist notwendig? */
	ssize_t r;
	
	/* 1.Zeile auslesen und testen ob Statuszeile des Headers in Ordnung*/	
	r = readline(sock, read_buff, MAXLINE); 
	/*Fehlerabfangen */
	if(r < 0){
		ERROR("Wasn't able to read")	
	}
	if(!strcmp(read_buff, "HTTP/1.1 200 OK")) {
		ERROR("Bad Request");
	}
		
	/*weiteren Header auslesen und ausgeben */
	while(1) {
		r = readline(sock, read_buff, MAXLINE); 
	
		/*Fehlerabfangen */
		if(r < 0){
			ERROR("Wasn't able to read")	
		}
		
		if(r==2) {
			break;
		}
		/*Ausgabe in der Konsole */		
		printf("%s ",read_buff);
	}
	
	/*restlichen Test in Datei speichern und Übungszettel ausgeben*/
	
	printf("\nDie Übungszettel: \n ");
	
	FILE * file;	
	file = fopen("zettel.html", "w");
	int err;
	if(file == NULL) {
		ERROR("File couldn't be opened")
	}
	while(1) {
		r = readline(sock, read_buff, MAXLINE); 

		/*Fehlerabfangen */
		if(r < 0){
			ERROR("Wasn't able to read")	
		}
		
		if(strstr(read_buff, "</body>")!= NULL) {
			break;
		}
		
		/* Schreiben in Datei */	

		err = fputs(read_buff, file);
		if(err < 0){
			ERROR("Wasn't able to write into file")	
		}
		
		/*Ausgeben der Übungszettel */
		int i=1;
		while(strstr(read_buff, "Uebungsblatt")!= NULL) {
			char search[50];
			sprintf(search, "Uebungsblatt0%i.pdf",i);
			
			if(strstr(read_buff, search) != NULL){
				printf("%s\n",search);
			}
			else {
				break;
			}
			i++;			
		}
	}
	
	err = fclose(file);
	if(err < 0){
			ERROR("Wasn't able to close the file")	
		}
	
	/* =0 Verbindungsabbau */
	
	/*close*/
	int clos;
	clos = close(sock);
	if(clos < 0){
			ERROR("Wasn't able to close the socket")	
		}
		
	printf("\nSocket erfolgreich geschlossen");
	
	return 0;
}