#include "util.h"
#include "transaction.h"
#include <stdio.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include "unp_readline.h"
#include <sys/select.h>
#include <stdlib.h>
/*
 * This structure encapuslated the complete server state
 */
typedef struct {
    int listen_fd; /* the listening socket, used to accept() new clients*/

    /*account infos*/
    int num_accounts;
    int *accounts;

    /*These variables store the state of the Clients
     * Clients in sate ACCEPTED (ready to send a port number), are stored in accepted
     * Clients in state WAITING (waiting for the release of an account, 
     * are stored in waiting_for_account, grouped by account
     * Clients in state MANAGING (currently operating on an account,
     * are stored in managing_account, grouped by account
     */
    fd_set accepted;
    fd_set *waiting_for_account;
    int *managing_account;
    
    /* read_fds contains _all_ file descriptors */
    fd_set read_fds;
    int max_fd; /*acutally never decremented, beware of ddos*/
} server_state;

int prepare_socket(int port, int *sock);
void init_state(server_state * state);
void close_client(int client, server_state *state);
void handle_event(server_state *state); 

void handle_new_client(server_state *state); 
void handle_transaction(int client, server_state *state); 
int is_managing(int client, server_state *state); 
void handle_account_request(int client, server_state *state); 
void shutdown_client(int client, server_state *state); 
int client_waiting_for(int acc, server_state *state); 
int is_waiting(int client, server_state *state); 


int main(int argc, char *argv[]) {
    int port , err;
    server_state state; //= {0};

    if(argc < 3) {
	printf("Usage: %s 'port' 'num_accounts'", argv[0]);		
	return 1;
    }

    port = atoi(argv[1]);
    state.num_accounts = atoi(argv[2]);
    if(port < 0)
	ERROR("Invalid port");

    if(state.num_accounts <= 0 || state.num_accounts >= 1000)
	ERROR("Invalid number of accounts");
    
    err = prepare_socket(port, &state.listen_fd);
    if(err < 0) ERROR("Could not prepare socket");

    ALLOC_OR(state.accounts, state.num_accounts)
	ERROR("No memory for accounts");
    
    init_state(&state);

    while(1) {
	handle_event(&state);
    }
}

void init_state(server_state *state) {
    FD_ZERO(&state->read_fds);
    FD_SET(state->listen_fd, &state->read_fds);
    state->max_fd = state->listen_fd;

    ALLOC_OR(state->waiting_for_account, state->num_accounts)
	ERROR("No memory");
    ALLOC_OR(state->managing_account, state->num_accounts)
	ERROR("No memory for managing accounts");
    for(int i = 0; i < state->num_accounts; i++)
	state->managing_account[i] = -1;
}
/*
 * The main select loop, distinguishes between events on listening socket, and connected clients
 */
void handle_event(server_state *state) {
    fd_set read_fds = state->read_fds; /*make a local copy of the fd_set to pass to select*/
    int num_ready = select(state->max_fd+1, &read_fds, NULL, NULL, NULL);

    if(num_ready <= 0)
	ERROR("select() failed");

    for(int i = 0; i <= state->max_fd; i++) {
	if(FD_ISSET(i, &read_fds)) {
	    if(i == state->listen_fd)
		handle_new_client(state);
	    else
		handle_transaction(i, state);
	}
    }
}

/*
 * Handles a new client,
 * sets him to state 'ACCEPTED' which means the client can now select an account
 */
void handle_new_client(server_state *state) {
    printf("Handling new cleint\n");
    int new_client = accept(state->listen_fd, NULL, NULL);
    if(new_client < 0) ERROR("Failed to accept()");

    FD_SET(new_client, &state->read_fds);
    FD_SET(new_client, &state->accepted);
    if(state->max_fd < new_client) state->max_fd = new_client;
    char response[20] = {0};
    sprintf(response, "%d", state->num_accounts);
    write(new_client, response, strlen(response));
}

/*
 * Distinguishes between an account request (state ACCEPTED) (which might set the client on hold)
 * And a transaction (state MANAGING)
 * Ignores clients in state WAIT
 */
void handle_transaction(int client, server_state *state) {
    int account, closed;
    if(FD_ISSET(client, &state->accepted)) {
	handle_account_request(client, state);
    } else if( (account = is_managing(client, state)) > 0) {
	closed = read_request(client, &state->accounts[account]);
	if(closed == 0)
	    shutdown_client(client, state);
    }
}

/*
 * Returns the account a client is currently managing
 */
int is_managing(int client, server_state *state) {
    for(int account = 0; account < state->num_accounts; account++) {
	if(state->managing_account[account] == client)
	    return account;
    }
    return -1;
}

/*
 * Handles the request of an account: a client in state ACCEPTED, that sent a account number
 * if the account is free , the client is set to state MANAGING
 * else to state WAITING
 */
void handle_account_request(int client, server_state *state) {
    //read which account the client wants
    printf("handling account request\n");
    char read_buff[300] = {0}; /*wieviel Platz ist notwendig? */
    ssize_t r;
    r = readline(client, read_buff, 300); 
    if(r == 0) { //client quit
	printf("closing client");
	close_client(client, state);
	return;
    }
    int account = atoi(read_buff);
    printf("requesting account %i\n", account);
    if(account < 0 || account >= state->num_accounts) {
	char message[] = "Invalid account, closing...";
	write(client, message, strlen(message));
	close_client(client, state);
    }
    if(state->managing_account[account] == -1) {
	printf("Account is free\n");
	state->managing_account[account] = client;
	write_account(client, &state->accounts[account]);
    } else {
	printf("client has to wait\n");
	FD_SET(client, &state->waiting_for_account[account]);
    }
    FD_CLR(client, &state->accepted);
}

/*
 * Terminates the session of a client in state MANAGING
 * Promotes a WAITING client to MANAGING, if such a client is present
 */
void shutdown_client(int client, server_state *state) {
    int managed_account = 0, c_waiting;
    for(; managed_account < state->num_accounts; managed_account++) {
	if(state->managing_account[managed_account] == client)
	    break;
    }
    state->managing_account[managed_account] = -1;
    if( (c_waiting = client_waiting_for(managed_account, state)) > 0 ) {
	FD_CLR(c_waiting, &state->waiting_for_account[managed_account]);
	state->managing_account[managed_account] = c_waiting;
	write_account(c_waiting, &state->accounts[managed_account]);
    } else {
	state->managing_account[managed_account] = -1;
    }
    close_client(client, state);
}

/*
 * If there is a client waiting for the given account, return the fd of this client, 
 * -1 otherwise
 */
int client_waiting_for(int acc, server_state *state) {
    for(int cl = 0; cl <= state->max_fd; cl++) {
	if(FD_ISSET(cl, &state->waiting_for_account[acc]))
	    return cl;
    }
    return -1;
}

/*
 * Closes the client-fd, and erases him from all fd_sets
 * does not do a state transition (use client_shutdown instead)
 */
void close_client(int client, server_state *state) {
    int m_acc, w_acc;
    
    if( (m_acc = is_managing(client, state)) > 0) {
	state->managing_account[m_acc] = -1;
    }
    if( (w_acc = is_waiting(client, state)) > 0) {
	FD_CLR(client, &state->waiting_for_account[w_acc]);
    }

    FD_CLR(client, &state->read_fds);
    FD_CLR(client, &state->accepted);
    close(client);
}

/*
 * Checks if the client is waiting for a account, and returns this account
 * -1 if the client is not waiting for anything
 */
int is_waiting(int client, server_state *state) {
    for(int acc = 0; acc < state->num_accounts; acc++) {
	if(FD_ISSET(client, &state->waiting_for_account[acc]))
		return acc;
    }
    return -1;
}
    

/*Input: A valid portnumber 'portnum', an int-pointer where the file descriptor of the new socket will be saved in
 * *
 * *Output: Negative numbers are error codes:
 * *
 * *Upon success the file descripter of the new socket will be in the int 'tcp_sock'
 * */
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
