#include "sender_handler.h"
 
 // code responsible for 

/* global variables */


/* function implementation */
void* sender_handler(void* _handler_args)
{
	printf("sender handler called here!\n");
	// extract networking information
	// initialize networking informaion
	    // networking information
    int sock;
    struct sockaddr_in client_addr;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr = inet_addr(LOCAL_SERVER_ADDR);
    client_addr.sin_port = htons(LOCAL_SERVER_PORT);
	
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
    
   if (connect(sock, (struct sockaddr *)&client_addr, sizeof(client_addr)) == -1)
    {
        printf("Error: connection unsuccessful!\n");
        exit(EXIT_FAILURE);
    }
	
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

void* join_server(void* _handler_args)
{
	// capture properties file, this should be the third arg

	// check for invalid properties file

	// check for console input being longer then JOIN

		// parse and capture the ip_addr

		// check for invalid ip_addr

			// back and ask for valid input

		// parse and capture the port

			// back and ask for valid input

		// set port to port from ____.properties

		// set ip_addr to id_addr from ____.properties

	// otherwise use the default values

		// use defines to grab default IP

		// use defines to grab default port

	// should set a flag of some sort so the user can't rejoin if they are already joined

	// stub return
	return 0;
}


