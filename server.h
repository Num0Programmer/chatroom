/************************************************************************
 * libraries
 ************************************************************************/
// should always be there ...
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// socket/bind/listen/accept
#include <arpa/inet.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

// read/write/close
#include <sys/uio.h>
#include <sys/types.h>
#include <unistd.h>

/************************************************************************
 * function prototype declarations
 ************************************************************************/
void handle_client(int client_socket);

/************************************************************************
 * preprocessor directives
 ************************************************************************/
#define SERVER_ADDR "142.11.213.134" // loopback ip address
#define PORT 23657              // port the server will listen on
#define NIST_DNS "time.nist.gov" // NIST server domain name
#define NIST_PORT 13 // port the NIST server listens on

// I cannot let go of the old-fashioned way :) - for readability ...
#define FALSE false
#define TRUE !false

// number of pending connections in the connection queue
#define NUM_CONNECTIONS 1

