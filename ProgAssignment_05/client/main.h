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
#include <syslog.h>
#include <time.h>
#include <unistd.h>

#include "../chat_node.h"
#include "../message.h"
#include "receiver_handler.h"
#include "sender_handler.h"
#include "../auxiliary/properties.c"


/* structures */


/* function prototypes */


/* preprocessor definitions */
#define FALSE 0
#define TRUE !FALSE
#define MAX_CHARS 80
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 25565
