#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include "mserver.h"

mserver *serv;

void handle_interrupt(int signum) {
	printf("\nProgram interrupted by user.\n");

	mserver_close(serv);
	free(serv);

	exit(signum);
}

int main() {
	signal(SIGINT, handle_interrupt);

	serv = malloc(sizeof(*serv));
	
	printf("Starting server.\n");
	mserver_setup(serv);
	mserver_bind(serv);

	mserver_start(serv);
	
	mserver_close(serv);
	free(serv);

	exit(EXIT_SUCCESS);
}
