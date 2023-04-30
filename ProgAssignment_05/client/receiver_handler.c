#include "receiver_handler.h"


/* global variables */
pthread_mutex_t mutex;


/* function implementation */
void* receiver_handler(void* receiver_port)
{
	// define networking information
	int receiver_socket;	// descriptor of reciever's socket
	struct sockaddr_in receiver_address;	// nameing the reciever's listening socket

	// initialize mutex
	pthread_mutex_init(&mutex, NULL);

	signal(SIGPIPE, SIG_IGN);	// sent on client disconnects
	
	if ((receiver_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		// report socket creation error
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	
	receiver_address.sin_family = AF_INET;	// define IP family
	receiver_address.sin_addr.s_addr = htonl(INADDR_ANY);	// accept on any port
	receiver_address.sin_port = htons(*((int*)receiver_port));	// port to listen on
	
	if (bind(
			receiver_socket,
			(struct sockaddr*)&receiver_address,
			sizeof(receiver_address)
		) != 0
	)
	{
		// report binding error
		perror("Error binding socket");
		exit(EXIT_FAILURE);
	}

	if (listen(receiver_socket, NUM_CONNECTIONS) != 0)
	{
		// report listening error
		perror("Error listening on socket");
		exit(EXIT_FAILURE);
	}

	/*
	printf("Receiver started:\n");
	printf("IP: %u\n", receiver_address.sin_addr.s_addr);
	printf("Port: %u\n", receiver_address.sin_port);
	*/

	// start receiver loop
	while (TRUE)
	{
		pthread_mutex_lock(&mutex);

		// accept client connection
		int conn_socket = accept(receiver_socket, NULL, NULL);

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

	// exit function
	if (close(receiver_socket) == -1)
	{
		perror("Error closing receiver socket");
		exit(EXIT_FAILURE);
	}
	pthread_mutex_destroy(&mutex);
	printf("end of receiver handler!\n");
	pthread_exit(NULL);	// reports status of conn to chatroom
}

void* handle_conn(void* _sock)
{
	// copy conn socket
	int conn_socket = *((int*)_sock);
	
	// unlock mutex
	pthread_mutex_unlock(&mutex);

	// default message structure
	struct message* msg = (struct message*)malloc(sizeof(struct message));
	msg->note = (struct note*)malloc(sizeof(struct note));

	read_message(msg, conn_socket);
	
	switch(msg->type)
	{
		case JOIN:
			fprintf(stdout, "%s %s\n", msg->note->username, msg->note->sentence);
			break;

		case LEAVE:
			fprintf(stdout, "You have left the room!\n");
			break;

		case SHUTDOWN:
			fprintf(stdout, "[%s] %s\n", msg->note->username, msg->note->sentence);
			exit(EXIT_SUCCESS);
			break;

		default:	
			fprintf(stdout, "[%s] %s\n", msg->note->username, msg->note->sentence);
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

