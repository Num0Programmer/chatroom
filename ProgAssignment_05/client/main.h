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

#include "receiver_handler.h"
#include "sender_handler.h"


/* structures */


/* function prototypes */


/* preprocessor definitions */
#define FALSE 0
#define TRUE !FALSE

