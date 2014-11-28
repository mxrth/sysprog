#ifndef __SOCKET_H__
#define __SOCKET_H__

int get_address(struct sockaddr_in *server_address);

int prepare_socket_tcp();

struct sockaddr_in getsockname_wrapper(int socketfd);






#endif
