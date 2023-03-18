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

/* function prototypes */
void* talk_to_server(void* _send);

/* Preprocessor directives */
#define HOME_ADDR "127.0.0.1"   // loopback ip address
#define SERVER_ADDR "142.11.213.134"   // ip address of server
#define PORT 23657              // port the server will listen on
#define DEFAULT_BUF_SIZE 64     // default size to set char arrays to

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 20       // number of pending connections in the connection queue

