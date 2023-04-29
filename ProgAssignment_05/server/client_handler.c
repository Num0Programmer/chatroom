#include "client_handler.h"


/* function implementation */
void* client_handler(void* _handler_args)
{
	// extract passed arguments
	struct handler_args* handler_args = (struct handler_args*)_handler_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&handler_args->sock);

	// unlock mutex
	pthread_mutex_unlock(handler_args->mutex);

	// allocate memory for incoming message
	struct message* rec_msg = (struct message*)malloc(sizeof(struct message));
	rec_msg->note = (struct note*)malloc(sizeof(struct note));
	// allocate memory for out going message
	struct message* send_msg = (struct message*)malloc(sizeof(struct message));
	send_msg->note = (struct note*)malloc(sizeof(struct note));

	// read a message from the socket
	read_message(rec_msg, client_socket);

	printf(
		"Received message from %u on port %u\n",
		rec_msg->ip_addr, rec_msg->port
	);
	printf(
		"[%s] %s: %hhu\n",
		rec_msg->note->username,
		rec_msg->note->sentence,
		rec_msg->note->length
	);
	
	// switch based on message type
	switch (rec_msg->type)
	{
		case JOIN:
			// set message information
			send_msg->type = JOIN;
			send_msg->port = rec_msg->port;
			send_msg->ip_addr = rec_msg->ip_addr;

			// set note information
			strcpy(send_msg->note->username, rec_msg->note->username);
			strcpy(send_msg->note->sentence, rec_msg->note->sentence);
			send_msg->note->length = 21;

			struct chat_node* new_client = (struct chat_node*)malloc(sizeof(struct chat_node));
			new_client->port = rec_msg->port;
			new_client->ip_addr = rec_msg->ip_addr;
			new_client->next_node = NULL;

			// add new client to list of chat nodes
			add_chat_node(handler_args->client_list, new_client);
			break;

		case LEAVE:
			break;

		case SHUTDOWN:
			break;

		case SHUTDOWN_ALL:
			break;

		default:
			break;
	}

	send_msg_to_room(handler_args->client_list, send_msg);

	// exit function
	close(client_socket);
	pthread_exit(NULL);	
}


void send_msg_to_room(struct chat_node_list* _list, struct message* _msg)
{
	struct chat_node* wrk_node = _list->head;

	while (wrk_node != NULL)
	{
		int sock;
		struct sockaddr_in send_addr;

		// create socket for sending
		if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		{
			perror("Error creating socket");
			exit(EXIT_FAILURE);
		}

		// set the address family
		send_addr.sin_family = AF_INET;
		// convert node's IP address and set the address
		send_addr.sin_addr.s_addr = inet_addr(ip_ntop(wrk_node->ip_addr));
		// set the port number
		send_addr.sin_port = htons(wrk_node->port);

		printf(
			"\tWriting message to %u on port %u\n",
			send_addr.sin_addr.s_addr, send_addr.sin_port
		);

		// connect to client's socket
		if (connect(sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1)
		{
			// report connection error
			perror("Error connection unsuccessful");
			exit(EXIT_FAILURE);
		}

		write_message(_msg, sock);
		close(sock);

		wrk_node = wrk_node->next_node;
	}
}

