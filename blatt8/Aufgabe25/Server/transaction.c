#include "transaction.h"

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
    /*Interpret request */char request[30];
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
    return 1;
}

void write_account(int newfd, int *acc) {
    /*writes account */
    ssize_t t;
    ssize_t count;
    char accountstr[30];
    sprintf(accountstr, "%i",*acc);
    count = strlen(accountstr)+1;
    t = write(newfd, accountstr, count);
    /*Überprüfung ob write() korrekt ausgeführt wurde */
    if(t < 0){
	ERROR("Wasn't able to write anything")
    }
    if(t < count){
	ERROR("Wasn't able to write everything")
    }
}

