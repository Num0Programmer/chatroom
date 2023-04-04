#include <pthread.h>
#include <stdio.h>
#include <unistd.h>


/* structures */
struct client
{
	int sock;
	struct client* next_client;
};

struct client_list
{
	size_t num_clients;
	struct client* head;
};


/* function prototypes */
void* client_handler(void* _socket);


/* preprocessor definitions */

