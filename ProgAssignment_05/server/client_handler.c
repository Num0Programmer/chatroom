#include "client_handler.h"


/* function implementation */
void* client_handler(void* _args)
{
	printf("client handler called here!\n");

	// msg to test received
	char msg[MSG_SIZE] = "this is a test";

	// making void* _args into usable handler_args
	struct handler_args* handler_args = (struct handler_args*)_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&handler_args->sock);

	// allocate memory for a message
	
	// unlock mutex
	
	// read a message from the socket
    read(client_socket, &msg, sizeof(char) * MSG_SIZE);
	printf("past read!\n");
	printf("Received: %s\n", msg);


	
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

