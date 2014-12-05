#ifndef _TRANSACTION_H
#define _TRANSACTION_H
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

void answer_bad_request(int newfd);
int read_request(int newfd, int *acc);

void write_account(int newfd, int *acc);

#endif
