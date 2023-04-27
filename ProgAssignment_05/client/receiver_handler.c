#include "receiver_handler.h"


/* global variables */
pthread_mutex_t mutex;


/* function implementation */
void* receiver_handler(void* rec_port)
{
	printf("\treceiver handler called here!\n");
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
	rec_address.sin_port = htons(*((int*)rec_port));	// port to listen on
	
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

	// indicate server is about to enter server loop
	printf("\tReceiver started:\n");
	printf("\tIP Address: %s\n", HOME_ADDR);
	printf("\tPort number: %d\n", *((int*)rec_port));

	// start receiver loop
	while (TRUE)
	{
		fprintf(stdout, "\tReceiver loop running...\n");
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

	// exit function
	pthread_mutex_destroy(&mutex);
	pthread_exit(NULL);	// reports status of conn to chatroom
}

void* handle_conn(void* _sock)
{
	printf("\t\thandle conn called here!\n");
	// copy conn socket
	int conn_socket = *((int*)_sock);
	// default message structure
	struct message* msg = (struct message*)malloc(sizeof(struct message));
	msg->note = (struct note*)malloc(sizeof(struct note));

	// unlock mutex
	pthread_mutex_unlock(&mutex);

	printf("\t\treading message from socket...\n");
	read_message(msg, conn_socket);
	printf("\t\tsuccessfully read message from the socket!\n");
	
	switch(msg->type)
	{
		case JOIN:
			printf("\t\tmessage was a JOIN message!\n");
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

