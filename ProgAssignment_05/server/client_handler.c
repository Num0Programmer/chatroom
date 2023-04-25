#include "client_handler.h"


/* function implementation */
void* client_handler(void* _handler_args)
{
	printf("client handler called here!\n");
	// define message construction variables
	struct message* msg = (struct message*)malloc(sizeof(struct message*));
	msg->note = (struct note*)malloc(sizeof(struct note));

	// extract passed arguments
	struct handler_args* handler_args = (struct handler_args*)_handler_args;

	// giving client_socket it's own variable
	int client_socket = *((int*)&handler_args->sock);

	// unlock mutex
	pthread_mutex_unlock(handler_args->mutex);

	// read a message from the socket
	read_message(msg, client_socket);
	printf("read the message:\n");
	printf("type: %d\n", msg->type);
	printf("port: %d\n", msg->port);
	printf("length: %d\n", msg->note->length);
	
	// switch based on message type
	switch (msg->type)
	{
		case JOIN:
			printf("join command\n");
			pthread_mutex_lock(handler_args->mutex);

			// leave what is necessary, this is mainly for debugging
			struct message* join_msg = (struct message*)malloc(sizeof(struct message));
			join_msg->note = (struct note*)malloc(sizeof(struct note));

			// set message information
			join_msg->type = JOIN;
			join_msg->port = client_socket;

			join_msg->ip_addr[0] = msg->ip_addr[0];
			join_msg->ip_addr[1] = msg->ip_addr[1];
			join_msg->ip_addr[2] = msg->ip_addr[2];
			join_msg->ip_addr[3] = msg->ip_addr[3];

			// set note information
			strcpy(join_msg->note->username, "[server]");
			strcpy(join_msg->note->sentence, "This is a join message!");
			join_msg->note->length = 23;

			struct chat_node* new_client = NULL;
			chat_node_init(new_client, msg->ip_addr, msg->port);
			printf("\tconstructed new client node!\n");

			// add new client to list of chat nodes
			add_chat_node(handler_args->client_list, new_client);

			write_message(join_msg, client_socket);

			// notify chat room of join
			notify_room(
				handler_args->client_list, msg->note->username, "joined"
			);

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case LEAVE:
			printf("leave command\n");
			pthread_mutex_lock(handler_args->mutex);

			/* debugging information message */
			struct message* leave_msg = (struct message*)malloc(sizeof(struct message));
			leave_msg->note = (struct note*)malloc(sizeof(struct note));

			// set message information
			leave_msg->type = LEAVE;
			leave_msg->port = msg->port;

			leave_msg->ip_addr[0] = msg->ip_addr[0];
			leave_msg->ip_addr[1] = msg->ip_addr[1];
			leave_msg->ip_addr[2] = msg->ip_addr[2];
			leave_msg->ip_addr[3] = msg->ip_addr[3];

			// set note information
			strcpy(leave_msg->note->username, "[server]");
			strcpy(leave_msg->note->sentence, "This is a leave message!");
			leave_msg->note->length = 24;

			write_message(leave_msg, client_socket);
			/* end of debugging message */

			// remove client from list of chat nodes
			remove_chat_node(handler_args->client_list, msg->ip_addr);

			// notify chat room of leave
			notify_room(handler_args->client_list, msg->note->username, "left");

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case SHUTDOWN:
			printf("shutdown command\n");
			pthread_mutex_lock(handler_args->mutex);

			/* debugging information message */
			struct message* shutdown_msg = (struct message*)malloc(sizeof(struct message));
			shutdown_msg->note = (struct note*)malloc(sizeof(struct note));

			// set message information
			shutdown_msg->type = SHUTDOWN;
			shutdown_msg->port = msg->port;

			shutdown_msg->ip_addr[0] = msg->ip_addr[0];
			shutdown_msg->ip_addr[1] = msg->ip_addr[1];
			shutdown_msg->ip_addr[2] = msg->ip_addr[2];
			shutdown_msg->ip_addr[3] = msg->ip_addr[3];

			// set note information
			strcpy(shutdown_msg->note->username, "[server]");
			strcpy(shutdown_msg->note->sentence, "This is a shutdown message!");
			shutdown_msg->note->length = 27;

			write_message(shutdown_msg, client_socket);
			/* end of debugging message */
			// send leave message to all chat nodes
			write_to_chat_node_list(handler_args->client_list, shutdown_msg);

			// remove client from list of chat nodes
			remove_chat_node(handler_args->client_list, msg->ip_addr);

			// notify chat room of leave
			notify_room(handler_args->client_list, msg->note->username, "left");

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case SHUTDOWN_ALL:
			printf("shutdown all command\n");
			pthread_mutex_lock(handler_args->mutex);

			/* debugging information message */
			struct message* all_shutdown_msg = (struct message*)malloc(sizeof(struct message));
			all_shutdown_msg->note = (struct note*)malloc(sizeof(struct note));

			// set message information
			all_shutdown_msg->type = SHUTDOWN;
			all_shutdown_msg->port = msg->port;

			all_shutdown_msg->ip_addr[0] = msg->ip_addr[0];
			all_shutdown_msg->ip_addr[1] = msg->ip_addr[1];
			all_shutdown_msg->ip_addr[2] = msg->ip_addr[2];
			all_shutdown_msg->ip_addr[3] = msg->ip_addr[3];

			// set note information
			strcpy(all_shutdown_msg->note->username, "[server]");
			strcpy(all_shutdown_msg->note->sentence, "This is a shutdown message!");
			all_shutdown_msg->note->length = 27;

			write_message(all_shutdown_msg, client_socket);
			/* end of debugging message */
			// send leave message to all chat nodes
			write_to_chat_node_list(handler_args->client_list, all_shutdown_msg);

			destroy_chat_node_list(handler_args->client_list);

			pthread_mutex_unlock(handler_args->mutex);
			break;

		default:
			printf("assumed note command\n");
			struct message* note_msg = (struct message*)malloc(sizeof(struct message));
			note_msg->note = (struct note*)malloc(sizeof(struct note));

			// set message information
			note_msg->type = NOTE;
			note_msg->port = msg->port;

			note_msg->ip_addr[0] = msg->ip_addr[0];
			note_msg->ip_addr[1] = msg->ip_addr[1];
			note_msg->ip_addr[2] = msg->ip_addr[2];
			note_msg->ip_addr[3] = msg->ip_addr[3];

			// set note information
			strcpy(note_msg->note->username, "[default user]");
			strcpy(note_msg->note->sentence, "This is a note message!");
			note_msg->note->length = 22;

			// send note message to all chat nodes
			write_to_chat_node_list(handler_args->client_list, note_msg);
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
