#include "sender_handler.h"
 
 // code responsible for 

/* global variables */


/* function implementation */
void* sender_handler(void* _message)
{
	printf("sender handler called here!\n");
	// define networking information

	// initialize networking informaion
	
	// connect to socket
	{
		// report socket creation error
		// exit program
	}

	// write MESSAGE
		// write type - htonl
		// write ip_addr - htonl
		// write port - htonl
	// write NOTE
		// write username
		// write sentence
		// write length - htonl

	// exit function
	// close socket
	pthread_exit(NULL);
}
