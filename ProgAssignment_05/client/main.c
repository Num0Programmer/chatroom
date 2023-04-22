#include "main.h"

// Should handle the connection with the server. One main loop to handle incoming requests and 
// out going messages/commands. 

/* global variables */
pthread_mutex_t mutex;


int main(int argc, char** argv)
{
	// define thread information
	pthread_t rec_thread;
	pthread_mutex_init(&mutex, NULL);
	// define funciton handler arguments
	struct handler_args* handler_args = (struct handler_args*)malloc(
		sizeof(struct handler_args)
	);

	// initialize client input c-string
	char client_input[MAX_CHARS];
	char *props_name = argv[1];

	// zero out clint_input
	memset(client_input, 0, MAX_CHARS);

	// capture command line input
	fgets(client_input, MAX_CHARS, stdin);

	// setting console_input and mutex
	// maybe make into a quick function?
	handler_args->console_input = client_input;
	handler_args->mutex = &mutex;
	handler_args->props_str = malloc(strlen(props_name) + 1);
	memcpy(handler_args->props_str, props_name, strlen(props_name) + 1);

	// start sender - pass networking information
	sender_handler((void*)handler_args);	// assuming unlocking a locked
											// mutex doesn't messup anything

	// start receiver thread - pass networking information
	pthread_create(&rec_thread, NULL, receiver_handler, NULL);

	// while chatting code is not equal to SHUTDOWN
	while (strcmp(client_input,"SHUTDOWN\n") != 0)
	{
		// zero out clint_input
		memset(client_input, 0, MAX_CHARS);

		// capture input from command line
		fgets(client_input, MAX_CHARS, stdin);

		// copying client_input into handler_args
		memcpy(handler_args->console_input, client_input, MAX_CHARS);

		// start sender thread - hand message to send
		pthread_t thread;
		if (pthread_create(&thread, NULL, sender_handler, (void*)handler_args) != 0)
		{
			perror("Error failure creating thread");
			exit(EXIT_FAILURE);
		}

		// check detach sender thread
		if (pthread_detach(thread) != 0)
		{
			perror("Error detaching thread");
			exit(EXIT_FAILURE);
		}

		pthread_mutex_lock(&mutex);
	}

	pthread_mutex_destroy(&mutex);
	return EXIT_SUCCESS;
}


/* function implementation */
