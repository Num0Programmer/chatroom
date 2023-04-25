#include "receiver_handler.h"


/* global variables */
pthread_mutex_t mutex;


/* function implementation */
void* receiver_handler(void* _)
{
	printf("receiver handler called here!\n");
	// define networking information
	int rec_socket;	// descriptor of reciever's socket
	struct sockaddr_in rec_address;	// nameing the reciever's listening socket

	// initialize mutex
	pthread_mutex_init(&mutex, NULL);

	signal(SIGPIPE, SIG_IGN);	// sent on client disconnects
	
	if ((rec_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		// report socket creation error
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	
	rec_address.sin_family = AF_INET;	// define IP family
	// accept server connection
	rec_address.sin_addr.s_addr = htonl(INADDR_ANY);
	rec_address.sin_port = htons(PORT);	// port to listen on
	
	if (bind(
			rec_socket,
			(struct sockaddr*)&rec_address,
			sizeof(rec_address)
		) != 0
	)
	{
		// report binding error
		perror("Error binding socket");
		exit(EXIT_FAILURE);
	}

	if (listen(rec_socket, NUM_CONNECTIONS) != 0)
	{
		// report listening error
		perror("Error listening on socket");
		exit(EXIT_FAILURE);
	}

	// start server loop
	while (TRUE)
	{
		pthread_mutex_lock(&mutex);

		// accept client connection
		int conn_socket = accept(rec_socket, NULL, NULL);

		// start deticated client thread
		pthread_t thread;
		if (pthread_create(
				&thread, NULL,
				handle_conn, (void*)&conn_socket
			) != 0
		)
		{
			// report thread creation error
			perror("Error creating thread for connection");
			exit(EXIT_FAILURE);
		}

		if (pthread_detach(thread) != 0)
		{
			// report thread detachment error
			perror("Error detaching thread");
			exit(EXIT_FAILURE);
		}
	}

	// destroy mutex
	pthread_exit(NULL);	// reports status of conn to chatroom
}

void* handle_conn(void* _sock)
{
	printf("handle conn called here!\n");
	// copy conn socket
	int conn_socket = *((int*)_sock);
	// default message structure
	struct message* msg = (struct message*)malloc(sizeof(struct message));
	msg->note = (struct note*)malloc(sizeof(struct note));

	// unlock mutex
	pthread_mutex_unlock(&mutex);

	// read message
	read_message(msg, conn_socket);
	
	switch(msg->type)
	{
		case JOIN:
			// print joining log
			break;

		case LEAVE:
			// print leaving log
			break;

		case SHUTDOWN:
			// print shutdown log
			break;

		// assume NOTE
		default:
			// print message
			break;
	}


	// exit function
	if (close(conn_socket) != 0)
	{
		// report closing socket error
		perror("Error closing client connection");
		exit(EXIT_FAILURE);
	}
	pthread_exit(NULL);
}

int read_complete(int _sock, int* int_ptr, size_t size)
{
	printf("read complete called here!\n");
	// define bytes read
	int bytes_read = 0;
	
	// loop until all bytes left is 0
	for (int bytes_left = 4; bytes_left > 0; bytes_left -= 1)
	{
		// read from network into int_ptr
		bytes_read = read(_sock, int_ptr, sizeof(size));

		// check all bytes read
		if (bytes_read == 4)
		{
			// return all bytes read
			return 4;
		}
		// check no bytes read
		else if (bytes_read == 0)
		{
			// return no bytes read
			return 0;
		}

		// shift int_ptr data left by bytes remaining
		*int_ptr <<= (bytes_left - bytes_read) * 8;
	}

	// return error in network
	return -1;
}
