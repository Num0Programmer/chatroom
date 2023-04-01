#include "client_handler.h"


/* function implementation */
void* client_handler(void* _socket)
{
	printf("client handler called here!\n");

	// networking information
	int socket = *((int*) _socket);
	char str[64] = "JOINED!";

	write(socket, &str, sizeof(char) * 64);

	// exit function
	pthread_exit(NULL);
}

