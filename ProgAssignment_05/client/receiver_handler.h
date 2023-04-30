#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "sender_handler.h"
#include "../chat_node.h"
#include "../message.h"
#include "../misc.h"


#ifndef RECEIVER_HANDLER_H
#define RECEIVER_HANDLER_H


/* structures */


/* function prototypes */
void* receiver_handler(void* _handler_args);
void* handle_conn(void* _sock);


/* preprocessor definitions */
#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 20


#endif /* RECEIVER_HANDLER_H */

