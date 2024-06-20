#include "mserver.h"

#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>

void mserver_setup(MSS) {
	#define SSA serv->server_address
	SSA.sin_family = AF_INET;
	SSA.sin_addr.s_addr = INADDR_ANY;
	SSA.sin_port = htons(25565);

	serv->server_address_len = sizeof(SSA);
	#undef SSA

	if ((serv->server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		printf("Error creating socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Socket created.\n");
}

void mserver_bind(MSS) {
	if (bind(serv->server_fd, (SA*)&serv->server_address, serv->server_address_len) == -1) {
		printf("Error bind socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	printf("Socket successfully binded.\n");
}

void mserver_start(MSS) {
	if (listen(serv->server_fd, 0) == -1) {
		printf("Listen error: %s\n", strerror(errno));

		mserver_close(serv);
		exit(EXIT_FAILURE);
	}

	printf("Listening for connections on %d\n", ntohs(serv->server_address.sin_port));

	while (true) {
		SAI client_address;
		unsigned int client_address_len = sizeof(SAI);
		int client_fd = accept(serv->server_fd, (SA*)&client_address, &client_address_len);

		if (client_fd == -1) {
			printf("Error accept client: %s\n", strerror(errno));
			
			close(client_fd);
			mserver_close(serv);
			exit(EXIT_FAILURE);
		}

		printf("Accepted client %d, IP: %s, PORT: %d", client_fd, inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

		close(client_fd);
	}
}

void mserver_close(MSS) {
	close(serv->server_fd);
}