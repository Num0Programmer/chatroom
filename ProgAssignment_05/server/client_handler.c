#include "client_handler.h"


/* function implementation */
void* client_handler(void* _args)
{
	printf("client handler called here!\n");
	int read_return;

	int command = 0;

	// zeroing out array
	// memset(msg, 0, MSG_SIZE);

	// msg to test received
	// define message construction variables

	struct message msg;

	// making void* _args into usable handler_args
	struct handler_args* handler_args = (struct handler_args*)_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&handler_args->sock);

	// allocate memory for a message
	
	// unlock mutex

	// read a message from the socket
	
    while (( read_return = read(client_socket, &msg, sizeof(struct message))) > 0)
	{
		printf("port: %d\n", msg.port);
		printf("length: %d\n", msg.note.length);
	}
	if (read_return < 0)
	{
		printf("read error \n");
	}
	
	// switch based on message type
	switch (command)
	{
		// case JOIN
		case JOIN:
			printf("join command\n");
			break;
			// lock mutex
			
			// initialize join message

			// add new client to list of chat nodes

			// notify chat room of join

			// send join message

			// unlock mutex
			// break

		// case LEAVE
		case LEAVE:
			printf("leave command\n");
			break;
			// lock mutex
			
			// remove client from list of chat nodes

			// notify chat room of leave

			// send leave message

			// unlock mutex
			// break

		// case SHUTDOWN
		case SHUTDOWN:
			printf("shutdown command\n");
			break;
			// lock mutex

			// initialize leave message

			// remove client from list of chat nodes

			// notify chat room of leave

			// send shutdown message

			// unlock mutex
			// break
		// case SHUTDOWN_ALL
		case SHUTDOWN_ALL:
			printf("shutdown all command\n");
			break;
			// lock mutex

			// initialize leave message

			// send leave message to all chat nodes

			// destroy chat node list

			// unlock mutex
			// break

		// assume NOTE
		default:
			printf("assumed note command\n");
			break;
			// initialize note message

			// send note message to all chat nodes
			
			// break
	}

	// exit function
	// close socket
	pthread_exit(NULL);
}

