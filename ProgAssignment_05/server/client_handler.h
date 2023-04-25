#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../chat_node.h"
#include "../message.h"

#define MSG_SIZE 80


/* structures */
struct handler_args
{
	int sock;
	struct chat_node_list* client_list;
	pthread_mutex_t* mutex;
};


/* function prototypes */
void* client_handler(void* _handler_args);
void notify_room(
	struct chat_node_list* _list,
	char username[16],
	char* msg_type
);


/* preprocessor definitions */
