#include "client_handler.h"

/* function implementation */
void* client_handler(void* arg)
{
	printf("client handler called here!\n");

	pthread_exit(NULL);
}

