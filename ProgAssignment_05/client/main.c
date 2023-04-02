#include "main.h"


/* global variables */
pthread_mutex_t mutex;


int main(int argc, char** argv)
{
	pthread_mutex_init(&mutex, NULL);

	pthread_t thread;
	if (pthread_create(&thread, NULL, receiver_handler, NULL) != 0)
	{
		perror("Error creating thread");
		exit(EXIT_FAILURE);
	}

	return EXIT_SUCCESS;
}

