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
    struct sockaddr_in server_addr;

	struct handler_args* handler_args = (struct handler_args*)_handler_args;


    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(handler_args->ip_addr);
    server_addr.sin_port = htons(handler_args->port);
	
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
   if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		// report socket creation error
        printf("Error: connection unsuccessful!\n");
		// exit program
        exit(EXIT_FAILURE);
    }

	char msg[MSG_SIZE]; 
	int sendbytes = strlen(handler_args->console_input);

	// copying console_input into msg with length of console_input + 1
	memcpy(msg, handler_args->console_input, sendbytes+1);
	
	 // write to server
    if(write(sock, msg, sendbytes) != sendbytes)
		printf("write error\n");


	// exit function
	// free message in handler args
	// close socket
	close(sock);

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


