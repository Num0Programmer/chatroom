#include <stdio.h>
#include <pthread.h>

#include "../chat_node.h"
#include "../message.h"


#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H


/* structures */
struct handler_args
{
	char* console_input;
	pthread_mutex_t* mutex;
};


/* function prototypes */
void* sender_handler(void* _handler_args);


/* preprocessor definitions */


#endif /* SENDER_HANDLER_H */

