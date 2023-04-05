#include <stdio.h>
#include <pthread.h>

#include "../chat_node.h"
#include "../message.h"


#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H


/* structures */
struct handler_args
{
	pthread_mutex_t* mutex;
	struct message* message;
};


/* function prototypes */
void* sender_handler(void* _message);


/* preprocessor definitions */


#endif /* SENDER_HANDLER_H */

