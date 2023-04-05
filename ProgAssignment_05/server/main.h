#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "../chat_node.h"
#include "client_handler.h"
#include "../message.h"


/* structures */


/* function prototypes */


/* preprocessor definitions */
#define SERVER_ADDR "127.0.0.1"
#define PORT 23657

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 20

