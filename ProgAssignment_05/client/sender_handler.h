#include <arpa/inet.h>
#include <pthread.h>
#define _GNU_SOURCE //this and unistd.h is here to support gettid for
#include <unistd.h> //distinguishing main threads from created threads
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include "../chat_node.h"
#include "../message.h"
#include "../auxiliary/properties.h"


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
	char* props_str;
	char* dest_ip_addr;
	int dest_port;
	int connected;	// this is a bool in accordance with TRUE FALSE macros
					// defined in main.h
};


/* function prototypes */
void* sender_handler(void* _handler_args);
void* join_server(void* _handler_args);
void load_props(struct handler_args* handler_args);

/* preprocessor definitions */
#define FALSE 0
#define TRUE !FALSE

#endif /* SENDER_HANDLER_H */
