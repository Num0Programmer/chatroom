#include "receiver_handler.h"


/* global variables */


/* function implementation */
void* receiver_handler()
{
	// connection information
	int sock;
	struct sockaddr_in client_addr;

	// function information
	char str[64];

	// initialize networking information
	sock = socket(AF_INET, SOCK_STREAM, 0);
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(HOME_ADDR);
	client_addr.sin_port = htons(PORT);

	// connect to socket
	if (connect(
			sock,
			(struct sockaddr*)&client_addr,
			sizeof(client_addr)
		) == -1
	)
	{
		perror("Error connecting to server");
		exit(EXIT_FAILURE);
	}

	read(sock, &str, sizeof(char) * 64);

	printf("Server: %s\n", str);

	// exit function
	close(sock);
	pthread_exit(NULL);
}
