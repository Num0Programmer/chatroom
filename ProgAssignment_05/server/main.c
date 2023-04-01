#include "main.h"

int main (int argc, char** argv)
{
	printf("Server started:\n");
	printf("IP Address: %s\n", SERVER_ADDR);
	printf("Port number: %d\n", PORT);

	int server_socket;					// descriptor of server socket
	struct sockaddr_in server_address;	// naming the server's listening socket

	signal(SIGPIPE, SIG_IGN);	// sent when client disconnected

	// create socket on which the server can listen
	if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}

	server_address.sin_family = AF_INET;				// define IP family
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);	// accept client
	server_address.sin_port = htons(PORT);				// port to listen on

	// bind socket to port
	if (bind(
			server_socket,
			(struct sockaddr*)&server_address,
			sizeof(server_address)
		) != 0
	)
	{
		perror("Error binding socket");
		exit(EXIT_FAILURE);
	}

	// listen for client conns (put in queue)
	if (listen(server_socket, NUM_CONNECTIONS) != 0)
	{
		perror("Error listening on socket");
		exit(EXIT_FAILURE);
	}

	// server loop
	while (TRUE)
	{
		// accept client
		int client_socket = accept(server_socket, NULL, NULL);
		printf("\nServer with PID %d: accepted client\n", getpid());

		// create and relegate client to dedicated thread
		pthread_t thread;
		if (pthread_create(&thread, NULL, client_handler, (void*)&client_socket) != 0)
		{
			perror("Error creating socket");
			exit(EXIT_FAILURE);
		}

		// detach thread
		if (pthread_detach(thread) != 0)
		{
			perror("Error detaching thread");
			exit(EXIT_FAILURE);
		}
	}

	return 0;
}

