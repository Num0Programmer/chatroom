#include "client_handler.h"


/* function implementation */
void* client_handler(void* _args)
{
	printf("client handler called here!\n");
	// int read_return;
	// int command;

	// define message construction variables
	struct message* msg = NULL;

	// extract passed arguments
	struct handler_args* handler_args = (struct handler_args*)_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&handler_args->sock);

	// unlock mutex
	pthread_mutex_unlock(handler_args->mutex);

	// read a message from the socket
	default_message(msg);
	printf("created a default message!\n");
	default_note(&msg->note);
	printf("assigned message note to default note");
	read_message(msg, client_socket);
	printf("read the message!\n");
	
	/*
    while ((read_return = read(client_socket, &msg, sizeof(struct message))) > 0)
	{
		printf("port: %d\n", msg->port);
		printf("length: %d\n", msg->note.length);
	}
	if (read_return < 0)
	{
		printf("read error \n");
	}
	*/

	// command = msg->type;
	
	// switch based on message type
	switch (msg->type)
	{
		case JOIN:
			printf("join command\n");
			pthread_mutex_lock(handler_args->mutex);

			struct chat_node* new_client = chat_node_init(
				msg->ip_addr, msg->port
			);
			printf("\tconstructed new client node!\n");

			// add new client to list of chat nodes
			add_chat_node(handler_args->client_list, new_client);

			// notify chat room of join
			notify_room(handler_args->client_list, msg->note.username, "joined");

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case LEAVE:
			printf("leave command\n");
			// lock mutex
			
			// remove client from list of chat nodes

			// notify chat room of leave

			// send leave message

			// unlock mutex
			break;

		case SHUTDOWN:
			printf("shutdown command\n");
			// lock mutex

			// initialize leave message

			// remove client from list of chat nodes

			// notify chat room of leave

			// send shutdown message

			// unlock mutex
			break;

		case SHUTDOWN_ALL:
			printf("shutdown all command\n");
			// lock mutex

			// initialize leave message

			// send leave message to all chat nodes

			// destroy chat node list

			// unlock mutex
			break;

		default:
			printf("assumed note command\n");
			// initialize note message

			// send note message to all chat nodes
			
			break;
	}

	// exit function
	close(client_socket);
	pthread_exit(NULL);	
}


void notify_room(
	struct chat_node_list* _list,
	char username[16],
	char* msg_type
)
{
	printf("%s has %s the room!\n", username, msg_type);
}

