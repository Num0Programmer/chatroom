#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "../chat_node.h"


/* structures */
struct handler_args
{
	int sock;
	struct chat_node_list* client_list;
	pthread_mutex_t* mutex;
};


/* function prototypes */
void* client_handler(void* _args);


/* preprocessor definitions */

