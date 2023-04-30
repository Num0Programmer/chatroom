#include "client_handler.h"


/* function implementation */
void* client_handler(void* _handler_args)
{
	// extract passed arguments
	struct handler_args* ha = (struct handler_args*)_handler_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&ha->sock);

	// unlock mutex
	//pthread_mutex_unlock(handler_args->mutex);

	// allocate memory for incoming message
	struct message* rec_msg = (struct message*)malloc(sizeof(struct message));
	rec_msg->note = (struct note*)malloc(sizeof(struct note));
	// allocate memory for out going message
	struct message* send_msg = (struct message*)malloc(sizeof(struct message));
	send_msg->note = (struct note*)malloc(sizeof(struct note));

	// read a message from the socket
	read_message(rec_msg, client_socket);

	if (rec_msg->type == NOTE)
	{
		// unlock mutex
		pthread_mutex_unlock(ha->mutex);
	}

	printf(
		"Received message from %s on port %d\n",
		ip_ntop(rec_msg->ip_addr), rec_msg->port
	);
	printf(
		"[%s] %s: %hhu\n",
		rec_msg->note->username,
		rec_msg->note->sentence,
		rec_msg->note->length
	);

	// set ambiguous message and note information
	send_msg->port = rec_msg->port;
	send_msg->ip_addr = rec_msg->ip_addr;
	memset(send_msg->note->sentence, 0, LEN_SENTENCE);
	strcpy(send_msg->note->username, rec_msg->note->username);
	
	// switch based on message type
	switch (rec_msg->type)
	{
		case JOIN:
			// set message information
			send_msg->type = JOIN;

			// set note information
			strcpy(send_msg->note->sentence, "has joined the room!");
			send_msg->note->length = 25;	// client always sends same message

			struct chat_node* new_client = (struct chat_node*)malloc(sizeof(struct chat_node));
			new_client->port = rec_msg->port;
			new_client->ip_addr = rec_msg->ip_addr;
			new_client->next_node = NULL;

			// add new client to list of chat nodes
			add_chat_node(ha->client_list, new_client);
			printf(
				"\t\tAdded client at %s on port %d to the list\n",
				ip_ntop(new_client->ip_addr), new_client->port
			);
			printf("\t\tRoom size: %zu\n", ha->client_list->size);
			// unlock mutex
			pthread_mutex_unlock(handler_args->mutex);
			break;

		case LEAVE:
			send_msg->type = LEAVE;

			strcpy(send_msg->note->sentence, "has left the room!");

			remove_chat_node(ha->client_list, rec_msg->ip_addr);
			printf(
				"\t\tRemoved client at %s on port %d from list\n",
				ip_ntop(rec_msg->ip_addr), rec_msg->port
			);
			printf("\t\tRoom size: %zu\n", ha->client_list->size);
			break;

		case SHUTDOWN:
			send_msg->type = LEAVE;
			
			strcpy(send_msg->note->sentence, "has left the room!");

			remove_chat_node(ha->client_list, rec_msg->ip_addr);
			printf(
				"\t\tRemoved client at %s on port %d from list\n",
				ip_ntop(rec_msg->ip_addr), rec_msg->port
			);
			printf("\t\tRoom size: %zu\n", ha->client_list->size);
			break;

		case SHUTDOWN_ALL:
			send_msg->type = SHUTDOWN_ALL;
			break;

		default:
			send_msg->type = NOTE;
			strcpy(send_msg->note->sentence, rec_msg->note->sentence);
			break;
	}
	// set connection information
	send_msg->port = rec_msg->port;
	send_msg->ip_addr = rec_msg->ip_addr;

	// set note information
	strcpy(send_msg->note->username, rec_msg->note->username);
	strcpy(send_msg->note->sentence, rec_msg->note->sentence);
	send_msg->note->length = strlen(send_msg->note->username);

	// forward message to room
	send_msg_to_room(handler_args->client_list, send_msg);

	// exit function
	if (close(client_socket) == -1)
	{
		perror("Error closing client socket");
		exit(EXIT_FAILURE);
	}
	pthread_exit(NULL);	
}


void send_msg_to_room(struct chat_node_list* _list, struct message* _msg)
{
	//printf("\n\t\tsend message to room called here!\n");
	struct chat_node* wrk_node = _list->head;

	while (wrk_node != NULL)
	{
		if(_msg->ip_addr != wrk_node->ip_addr)
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

			// connect to client's socket
			if (connect(sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1)
			{
				// report connection error
				perror("Error connection unsuccessful");
				exit(EXIT_FAILURE);
			}
		
			write_message(_msg, sock);
			printf("\nWrote message to %s\n", ip_ntop(wrk_node->ip_addr));
			
			if (close(sock) == -1)
			{
				perror("Error closing client socket");
				exit(EXIT_FAILURE);
			}
		}
		wrk_node = wrk_node->next_node;
	}
}

