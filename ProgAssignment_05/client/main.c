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
	// define networking information
	struct handler_args* handler_args = (struct handler_args*)malloc(
		sizeof(struct handler_args)
	);

	// initialize client input c-string
	char client_input[MAX_CHARS];
	memset(client_input, 0, sizeof client_input);

	// capture command line input
	fgets(client_input, MAX_CHARS, stdin);
	
	// used to do initial conn in send and rec handlers
	struct message* join_message = (struct message*)malloc(
		sizeof(struct message)
	);
	// check input length is greater than "JOIN"
	if (strlen(client_input) > strlen("JOIN"))
	{
		// initialize networking information with custom information
		printf("Custom info \n");
		
	}
	else // otherwise, assume default configuration information
	{
		// initialize networking information with default information
		printf("default info \n");
	}
	handler_args->mutex = &mutex;

	// start sender - pass networking information
	sender_handler((void*)&handler_args);	// assuming unlocking a locked
											// mutex doesn't messup anything

	// start receiver thread - pass networking information
	pthread_create(&rec_thread, NULL, receiver_handler, (void*)join_message);
	free(join_message);	// served use of setting up receiver thread

	// while chatting code is not equal to SHUTDOWN
	while (strcmp(client_input,"SHUTDOWN\n") != 0)
	{
		// capture input from command line
		fgets(client_input, MAX_CHARS, stdin);

		struct message my_message;
		// build message
		handler_args->message = &my_message;

		// start sender thread - hand message to send
		pthread_t thread;
		if (pthread_create(&thread, NULL, sender_handler, (void*)&handler_args) != 0)
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

