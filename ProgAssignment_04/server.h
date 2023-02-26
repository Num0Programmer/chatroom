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
#include <syslog.h>
#include <time.h>

/* Function prototypes */
void* handle_client(void* arg);
int collatz_conj(int num);

/* Preprocessor directives */
#define SERVER_ADDR "127.0.0.1" // loopback ip address
#define PORT 23657              // port the server will listen on
#define NIST_DNS "time.nist.gov"
#define NIST_IP "129.6.15.28"
#define NIST_PORT 13
#define MSG_SIZE 100

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 1       // number of pending connections in the connection queue

