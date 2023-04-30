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
#include "../auxiliary/properties.h"


/* structures */


/* function prototypes */
int command_read(char* input_string);
void* join_room(void* _handler_args, char* input_string);
void load_props(struct handler_args* _handler_args);
void print_join_help();


/* preprocessor definitions */
#define DEFAULT_IP "127.0.0.1"
#define DEFAULT_PORT 23657

#define MAX_CHARS 128

#define FALSE 0
#define TRUE !FALSE

