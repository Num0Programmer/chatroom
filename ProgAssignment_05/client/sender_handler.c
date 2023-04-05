#include "sender_handler.h"
 
 // code responsible for 

/* global variables */


/* function implementation */
void* sender_handler(void* _handler_args)
{
	printf("sender handler called here!\n");
	// extract networking information
	// initialize networking informaion
	
	// define message construction variables
	
	// switch based on command
	{
		// case JOIN
		// case LEAVE
		// case SHUTDOWN
		// case SHUTDOWN_ALL
		// assume NOTE
	}
	
	// unlock mutex
	
	// connect to socket
	{
		// report socket creation error
		// exit program
	}

	// write message

	// exit function
	// free message in handler args
	// close socket
	pthread_exit(NULL);
}
