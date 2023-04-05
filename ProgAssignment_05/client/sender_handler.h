#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../chat_node.h"
#include "../message.h"


#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H


/* structures */
struct handler_args
{
	char* console_input;
	pthread_mutex_t* mutex;
	char* ip_addr;
	int port;
};


/* function prototypes */
void* sender_handler(void* _handler_args);


/* preprocessor definitions */


#endif /* SENDER_HANDLER_H */

