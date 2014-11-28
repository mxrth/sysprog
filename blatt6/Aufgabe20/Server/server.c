#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "util.h"
#include <errno.h>

#include <string.h>
#include "unp_readline.h"

/*Input: A valid portnumber 'portnum', an int-pointer where the file descriptor of the new socket will be saved in 
 *
 *Output: Negative numbers are error codes:
 *
 *Upon success the file descripter of the new socket will be in the int 'tcp_sock'
 */
int prepare_socket(int portnum, int *tcp_sock)
{
	int err;
	struct sockaddr_in myaddr;

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(portnum);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	
	*tcp_sock = socket(AF_INET,SOCK_STREAM,0);
	if(*tcp_sock < 0){
		return -1;
	}

	err = bind(*tcp_sock, (struct sockaddr*) &myaddr, sizeof(struct sockaddr_in));
	if(err < 0){
		return -2;	
	}

	/*Setting socket into passive mode*/
	err = listen(*tcp_sock, 5);
	if(err < 0){
		return -3;	
	}

	return 0;
}

void write_account(int newfd, int *acc) {
	/*writes account */

	ssize_t t;
	ssize_t count;
	char accountstr[30];
	
	sprintf(accountstr, "%i",*acc);
	
	count = strlen(accountstr)+1;
	t =	write(newfd, accountstr, count); 
	
	/*Überprüfung ob write() korrekt ausgeführt wurde */
	if(t < 0){
		ERROR("Wasn't able to write anything")	
	}
	if(t < count){
		ERROR("Wasn't able to write everything")	
	}

}

void answer_bad_request(int newfd) {
	/*answer bad request */
	ssize_t t;
	ssize_t count;
	char str[30];
	strcpy(str, "This request is not valid\n");
	
	count = strlen(str)+1;
	t = write(newfd, str, count); 
	
	/*Überprüfung ob write() korrekt ausgeführt wurde. */
	if(t < 0){
		ERROR("Wasn't able to write anything")	
	}
	if(t < count){
		ERROR("Wasn't able to write everything")	
	}
}

int read_request(int newfd, int *acc) {
	/* read() */
	
	char read_buff[300]; /*wieviel Platz ist notwendig? */
	ssize_t r;
	int err;
	
	/* readline and decide what needs to be done */	
	r = readline(newfd, read_buff, 300); 
	
	/*Error handling */
	if(r < 0){
		ERROR("Wasn't able to read")	
	}
	if(r==0){
		return 0;
	}

	printf("Client send: %s\n",read_buff);

	/*check if request is of valid format */



	/*Interpret request */		
	char request[30];
	int amount = 0;

	err = sscanf(read_buff, "%s %d", request, &amount);
	if(err != 2) {
		answer_bad_request(newfd);
	}

	if(strstr(request, "Deposit")!= NULL) {
		*acc += amount;
		printf("Deposit succesfull. New account: %i\n", *acc);
		write_account(newfd,acc);
		return 1;

	}
	if(strstr(request, "Withdraw")!= NULL) {
		*acc -= amount;
		printf("Withdraw succesfull. New account: %i\n", *acc);
		write_account(newfd,acc);
		return 1;
	}
	else {
		answer_bad_request(newfd);
	}

}

void treat_request(int newfd, int *acc) {
	int discon;
	write_account(newfd, acc);
	/*reads and interprets request and calls write_account after fullfilling them */
	while(1) {
		discon = read_request(newfd, acc);
		if (discon==0) {
			return;
		}
	}
}


int main(int argc, char **argv) {

	int account = 0;
	int portnumber;
	int err;

	/*checking and getting input*/
	if(argc <2){
		ERROR("Not the right amount of input parameters\n Use like this: ./tcpserver 'Portnumber'")
	}
	portnumber = atoi(argv[1]);

	if(portnumber < 0){
		ERROR("Invalid portnumber")	
	}

	printf("Server is going to handle requests on port %i\n", portnumber);


	/*Preparing*/
	int sockListenFd;
	int newfd;
	struct sockaddr client;
	socklen_t len;

	err = prepare_socket(portnumber, &sockListenFd);

	if (err == -1) {
		ERROR("Could not create socket\n")
		return 1;
	}
	if (err == -2) {
		ERROR("Could not bind socket\n")
		return 1;
	}
	if (err == -3) {
		ERROR("Could not put socket into listening mode\n")
		return 1;
	}


	while(1) {
		len = sizeof(client);
		newfd = accept(sockListenFd, &client, &len);
		if(newfd < 0) {
			ERROR("Could not accept")
		}
		
		printf("\nconnection succesfull\n");	
		

		treat_request(newfd, &account);
		err = close(newfd);

		if(err < 0){
			ERROR("Couldn't close socket")
		}
		
		printf("closed connection succesfully\n");
		

	}

	err = close(sockListenFd);

	if(err < 0){
		ERROR("Couldn't close socket")
	}
	return 0;
}
