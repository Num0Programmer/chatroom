#include "sender_handler.h"
 
// code responsible for 

/* global variables */


/* function implementation */
void* sender_handler(void* _handler_args)
{
	int sock;
	struct handler_args* ha = (struct handler_args*)_handler_args;
    struct sockaddr_in server_addr;

	// filling in socket info
	sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ha->dest_ip_addr);
    server_addr.sin_port = htons(ha->dest_port);

	// connect to socket
	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		// report socket creation error
        perror("Error connection unsuccessful");
        exit(EXIT_FAILURE);
    }

	// write to server
	write_message(ha->msg, sock);

	// unlock mutex
	pthread_mutex_unlock(ha->mutex);

	// exit function
	if (close(sock) == -1)
	{
		perror("Error closing sender socket");
		exit(EXIT_FAILURE);
	}
	pthread_exit(NULL);
}

