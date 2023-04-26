#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../chat_node.h"
#include "../message.h"


#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H


/* structures */
struct handler_args
{
	int sock;
	struct chat_node_list* client_list;
	pthread_mutex_t* mutex;
};


/* function prototypes */
void* client_handler(void* _handler_args);
void send_msg_to_room(struct chat_node_list* _list, struct message* _msg);


/* preprocessor definitions */
#define MSG_SIZE 80


#endif /* CLIENT_HANDLER_H */

