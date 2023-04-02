#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>


/* structures */


/* function prototypes */
void* receiver_handler(void* _);
void* handle_conn(void* _sock);
int read_complete(int _sock, int* int_value_ptr, size_t size);


/* preprocessor definitions */
#define HOME_ADDR "127.0.0.1"
#define SERVER_ADDR "142.11.213.134"
#define PORT 23657

