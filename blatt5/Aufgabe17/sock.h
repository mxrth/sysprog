#ifndef __SOCK_H__
#define __SOCK_H__


int prepare_socket(int portnum, int *tcp_sock);

int manage_connections(int anzverbindungen,int tcp_sock, int (*managerfunction) (FILE * datastream, char *information));

int print_port(int sock);


int close_socket(int sock);




#endif
