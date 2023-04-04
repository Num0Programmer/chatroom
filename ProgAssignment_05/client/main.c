#include "main.h"

// Should handle the connection with the server. One main loop to handle incoming requests and 
// out going messages/commands. 

/* global variables */

int main(int argc, char** argv)
{
	char client_input[MAX_CHARS];
	pthread_t thread;
	pthread_t thread2;

	//zero out array
	memset(client_input, 0, sizeof client_input);

	// define threading information
	// define networking information

	// capture command line input
	fgets(client_input, MAX_CHARS, stdin);
	
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
		
	// start sender - pass networking information
	sender_handler(0);

	// start receiver thread - pass networking information
	pthread_create(&thread2, NULL, receiver_handler, (void*)0);

	// while chatting code is not equal to SHUTDOWN
	while (strcmp(client_input,"SHUTDOWN\n") != 0)
	{
		// capture input from command line
		fgets(client_input, MAX_CHARS, stdin);

		// start sender thread - hand port number
		pthread_create(&thread, NULL, sender_handler, (void*)client_input);

		// check join with sender thread
		{
			// report errors
		}
		
	}

	return EXIT_SUCCESS;
}


/* function implementation */

