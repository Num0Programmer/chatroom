#include "client_handler.h"


/* function implementation */
void* client_handler(void* _args)
{
	printf("client handler called here!\n");
	// cast incoming arguments back to handler_args
	// extract socket
	// allocate memory for a message
	
	// unlock mutex
	
	// read a message from the socket
	
	// switch based on message type
	{
		// case JOIN
			// lock mutex
			
			// initialize join message

			// add new client to list of chat nodes

			// notify chat room of join

			// send join message

			// unlock mutex
			// break
		// case LEAVE
			// lock mutex
			
			// remove client from list of chat nodes

			// notify chat room of leave

			// send leave message

			// unlock mutex
			// break
		// case SHUTDOWN
			// lock mutex

			// initialize leave message

			// remove client from list of chat nodes

			// notify chat room of leave

			// send shutdown message

			// unlock mutex
			// break
		// case SHUTDOWN_ALL
			// lock mutex

			// initialize leave message

			// send leave message to all chat nodes

			// destroy chat node list

			// unlock mutex
			// break
		// assume NOTE
			// initialize note message

			// send note message to all chat nodes
			
			// break
	}

	// exit function
	// close socket
	pthread_exit(NULL);
}

