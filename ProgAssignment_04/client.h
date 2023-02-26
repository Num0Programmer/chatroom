#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <syslog.h>
#include <time.h>

/* Function prototypes */
void* talk_to_server(void *number_ptr);

/* Preprocessor directives */
#define HOME_ADDR "127.0.0.1"   // loopback ip address
#define HOME_PORT 23657
#define SERVER_ADDR "0.0.0.0"   // ip address of server
#define PORT 23657              // port the server will listen on
#define DEFAULT_BUF_SIZE 64     // default size to set char arrays to

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 1       // number of pending connections in the connection queue

