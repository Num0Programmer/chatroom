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
			send_msg->port = rec_msg->port;
			send_msg->ip_addr = rec_msg->ip_addr;

			// set note information
			strcpy(send_msg->note->username, rec_msg->note->username);
			strcpy(send_msg->note->sentence, rec_msg->note->sentence);
			send_msg->note->length = 23;

			struct chat_node* new_client = (struct chat_node*)malloc(sizeof(struct chat_node));
			new_client->port = rec_msg->port;
			new_client->ip_addr = rec_msg->ip_addr;
			new_client->next_node = NULL;
			printf("username: %s\n", rec_msg->note->username);

			printf("Client with IP: %s\n", ip_ntop(new_client->ip_addr));
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
	int sock;
	struct chat_node* wrk_node = _list->head;

	while (wrk_node != NULL)
	{
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

		printf("\t\t\tWriting message to:\n");
		printf("\t\t\tIP: %u\n", send_addr.sin_addr.s_addr);
		printf("\t\t\tPort: %u\n", send_addr.sin_port);

		// connect to client's socket
		printf("\t\t\tAttempting connection...\n");
		if (connect(sock, (struct sockaddr*)&send_addr, sizeof(send_addr)) == -1)
		{
			// report connection error
			perror("Error connection unsuccessful");
			exit(EXIT_FAILURE);
		}
		printf("\t\t\tConnection was successful!\n");

		write_message(_msg, sock);

		printf("\t\t\tmessage on to client!\n");
		wrk_node = wrk_node->next_node;
	}

	// exit function
	close(sock);
}

