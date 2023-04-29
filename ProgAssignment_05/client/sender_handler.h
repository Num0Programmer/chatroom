#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> //distinguishing main threads from created threads

#include "../chat_node.h"
#include "../message.h"
#include "../auxiliary/properties.h"


#ifndef SENDER_HANDLER_H
#define SENDER_HANDLER_H


/* structures */
struct handler_args
{
	struct message* msg;
	char* ip_addr;
	int port;
	char* props_str;
	char* dest_ip_addr;
	int dest_port;
	int connected;	// this is a bool in accordance with TRUE FALSE macros
					// defined in main.h
	pthread_mutex_t* mutex;
};


/* function prototypes */
void* sender_handler(void* _handler_args);

/* preprocessor definitions */
#define _GNU_SOURCE //this and unistd.h is here to support gettid for

#define FALSE 0
#define TRUE !FALSE

#define MSG_SIZE 80
#define SERVER_ADDR "142.11.213.134"
#define LOCAL_SERVER_ADDR "127.0.0.1"
#define LOCAL_SERVER_PORT 23657


#endif /* SENDER_HANDLER_H */
