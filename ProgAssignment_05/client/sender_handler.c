#include "sender_handler.h"


/* global variables */


/* function implementation */
void* sender_handler(void* _)
{
	printf("sender handler called here!\n");

	pthread_exit(NULL);
}
