#include <stdio.h>
#include <stdlib.h>

#include "mserver.h"

int main() {
	mserver *serv = malloc(sizeof(*serv));
	
	printf("Starting server.\n");
	mserver_setup(serv);
	mserver_bind(serv);

	mserver_start(serv);
	
	mserver_close(serv);
	free(serv);

	exit(EXIT_SUCCESS);
}
