#include "client_handler.h"


/* function implementation */
void* client_handler(void* _handler_args)
{
	printf("client handler called here!\n");
	// allocate memory for incoming message
	struct message* rec_msg = (struct message*)malloc(sizeof(struct message));
	rec_msg->note = (struct note*)malloc(sizeof(struct note));
	// allocate memory for out going message
	struct message* send_msg = (struct message*)malloc(sizeof(struct message));
	send_msg->note = (struct note*)malloc(sizeof(struct note));

	// extract passed arguments
	struct handler_args* handler_args = (struct handler_args*)_handler_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&handler_args->sock);

	// unlock mutex
	pthread_mutex_unlock(handler_args->mutex);

	// read a message from the socket
	read_message(rec_msg, client_socket);
	
	// switch based on message type
	switch (rec_msg->type)
	{
		case JOIN:
			printf("join command\n");
			// set message information
			send_msg->type = JOIN;
			send_msg->port = client_socket;

			strcpy(send_msg->ip_addr, rec_msg->ip_addr);

			// set note information
			strcpy(send_msg->note->username, "[server]");
			strcpy(send_msg->note->sentence, "This is a join message!");
			send_msg->note->length = 23;

			struct chat_node* new_client = (struct chat_node*)malloc(sizeof(struct chat_node));
			new_client->port = rec_msg->port;
			strcpy(new_client->ip_addr, rec_msg->ip_addr);
			new_client->next_node = NULL;

			printf("Client with IP: %s\n", new_client->ip_addr);
			printf("Port: %d\n", new_client->port);
			printf("Was added!\n");

			// add new client to list of chat nodes
			add_chat_node(handler_args->client_list, new_client);
			break;

		case LEAVE:
			printf("leave command\n");
			break;

		case SHUTDOWN:
			printf("shutdown command\n");
			break;

		case SHUTDOWN_ALL:
			printf("shutdown all command\n");
			break;

		default:
			printf("assumed note command\n");
			break;
	}

	printf("\t\tsending message to room...\n");
	send_msg_to_room(handler_args->client_list, send_msg);
	printf("\t\troom now has message!\n");

	// exit function
	close(client_socket);
	pthread_exit(NULL);	
}


void send_msg_to_room(struct chat_node_list* _list, struct message* _msg)
{
	struct chat_node* wrk_node = _list->head;

	while (wrk_node != NULL)
	{
		printf("\t\t\tWriting message to:\n");
		printf("\t\t\tIP: %s\n", wrk_node->ip_addr);
		printf("\t\t\tPort: %d\n", wrk_node->port);
		write_message(_msg, wrk_node->port);
		printf("\t\t\tmessage on to client!\n");
		wrk_node = wrk_node->next_node;
	}
}

