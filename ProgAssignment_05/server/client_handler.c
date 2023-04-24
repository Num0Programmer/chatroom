#include "client_handler.h"


/* function implementation */
void* client_handler(void* _args)
{
	printf("client handler called here!\n");
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
	default_note(&msg->note);
	read_message(msg, client_socket);
	printf("read the message:\n");
	printf("type: %d\n", msg->type);
	printf("port: %d\n", msg->port);
	printf("length: %d\n", msg->note.length);
	
	// switch based on message type
	switch (msg->type)
	{
		case JOIN:
			printf("join command\n");
			pthread_mutex_lock(handler_args->mutex);

			struct chat_node* new_client = NULL;
			chat_node_init(new_client, msg->ip_addr, msg->port);
			printf("\tconstructed new client node!\n");

			// add new client to list of chat nodes
			add_chat_node(handler_args->client_list, new_client);

			// notify chat room of join
			notify_room(
				handler_args->client_list, msg->note.username, "joined"
			);

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case LEAVE:
			printf("leave command\n");
			pthread_mutex_lock(handler_args->mutex);
			
			// remove client from list of chat nodes
			remove_chat_node(handler_args->client_list, msg->ip_addr);

			// notify chat room of leave
			notify_room(handler_args->client_list, msg->note.username, "left");

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case SHUTDOWN:
			printf("shutdown command\n");
			pthread_mutex_lock(handler_args->mutex);

			// remove client from list of chat nodes
			remove_chat_node(handler_args->client_list, msg->ip_addr);

			// notify chat room of leave
			notify_room(handler_args->client_list, msg->note.username, "left");

			pthread_mutex_unlock(handler_args->mutex);
			break;

		case SHUTDOWN_ALL:
			printf("shutdown all command\n");
			pthread_mutex_lock(handler_args->mutex);

			struct message* shutdown_msg = NULL;
			default_message(msg);	// change with message_init()

			// send leave message to all chat nodes
			write_to_chat_node_list(handler_args->client_list, shutdown_msg);

			destroy_chat_node_list(handler_args->client_list);

			pthread_mutex_unlock(handler_args->mutex);
			break;

		default:
			printf("assumed note command\n");
			struct message* note_msg = NULL;
			default_message(note_msg);

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

