#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>


#include "../chat_node.h"
#include "../message.h"

#define MSG_SIZE 80

#define LOCAL_SERVER_ADDR "127.0.0.1"
#define LOCAL_SERVER_PORT 23657

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
void* join_server(void* _handler_args);
int command_read(char* input_string);


/* preprocessor definitions */


#endif /* SENDER_HANDLER_H */

