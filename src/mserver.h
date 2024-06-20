#pragma once

#include <netinet/in.h>
#include <sys/socket.h>

#define SAI struct sockaddr_in
#define SA struct sockaddr

typedef struct {
	SAI server_address;
	int server_address_len;
	int server_fd;
} mserver;

#define MSS mserver* serv

void mserver_setup(MSS);
void mserver_bind(MSS);
void mserver_start(MSS);
void mserver_close(MSS);
