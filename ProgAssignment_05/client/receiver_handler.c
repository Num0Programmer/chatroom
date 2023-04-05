#include "receiver_handler.h"


/* global variables */
pthread_mutex_t mutex;


/* function implementation */
void* receiver_handler(void* _)
{
	printf("receiver handler called here!\n");
	// define networking information

	// initialize mutex

	// create client disconnect signal
	
	// create socket
	{
		// report socket creation error
		// exit program
	}
	
	// initialize networking information
	
	// bind socket to port
	{
		// report binding error
		// exit program
	}

	// start listening on port
	{
		// report listening error
		// exit program
	}

	// start server loop
	{
		// lock mutex

		// accept client connection

		// start deticated client thread
		{
			// report thread creation error
			// exit program
		}

		// detach thread
		{
			// report thread detachment error
			// exit program
		}
	}

	// destroy mutex
	pthread_exit(NULL);	// reports status of conn to chatroom
}

void* handle_conn(void* _sock)
{
	printf("handle conn called here!\n");
	// copy conn socket
	// default message structure

	// unlock mutex

	// write MESSAGE
		// write type - ntoh
		// write ip_addr - ntoh
		// write port - ntoh
	// write NOTE
		// write username
		// write sentence
		// write length - ntoh
	
	// switch based on message type
	{
		// case JOIN
			// print joining log

		// case LEAVE
			// print leaving log

		// case SHUTDOWN
			// print shutdown log

		// assume NOTE
			// print message
	}

	// close socket
	{
		// report closing socket error
		// exit program
	}

	pthread_exit(NULL);
}

int read_complete(int _sock, int* int_value_ptr, size_t size)
{
	printf("read complete called here!\n");
	// define bytes read
	
	// loop until all bytes left is 0
	{
		// read from network into int_value_ptr

		// check all bytes read
		{
			// return all bytes read
		}
		// check no bytes read
		{
			// return no bytes read
		}

		// shift int_value_ptr data left by bytes remaining
	}

	return -1;
}

