#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include "sender_handler.h"
#include "../chat_node.h"
#include "../message.h"


#ifndef RECEIVER_HANDLER_H
#define RECEIVER_HANDLER_H


/* structures */


/* function prototypes */
void* receiver_handler(void* rec_port);
void* handle_conn(void* _sock);
int read_complete(int _sock, int* int_value_ptr, size_t size);


/* preprocessor definitions */
#define FALSE 0
#define TRUE !FALSE

#define HOME_ADDR "127.0.0.1"
#define PORT 23657
#define NUM_CONNECTIONS 20


#endif /* RECEIVER_HANDLER_H */

