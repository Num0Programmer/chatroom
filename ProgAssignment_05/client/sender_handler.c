#include "sender_handler.h"
 
 // code responsible for 

/* global variables */


/* function implementation */
void* sender_handler(void* _handler_args)
{
	printf("sender handler called here!\n");
	// extract networking information
	// initialize networking informaion
	    // networking information
    int sock;
	int command = 0;
    struct sockaddr_in server_addr;

	struct handler_args* handler_args = (struct handler_args*)_handler_args;


    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(handler_args->ip_addr);
    server_addr.sin_port = htons(handler_args->port);
	
	// define message construction variables

	// capture command
	command = command_read(handler_args->console_input);
	
	// switch based on command
	switch (command)
	{
		case JOIN:
		printf("join command\n");
		break;

		case LEAVE:
		printf("leave command\n");
		break;

		case SHUTDOWN:
		printf("shutdown command\n");
		break;

		case SHUTDOWN_ALL:
		printf("shutdownn command\n");
		break;
	
		default:
		printf("assumed note command\n");
		break;

	}
	
	// unlock mutex
    
	// connect to socket
   if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		// report socket creation error
        printf("Error: connection unsuccessful!\n");
		// exit program
        exit(EXIT_FAILURE);
    }

	char msg[MSG_SIZE]; 
	int sendbytes = strlen(handler_args->console_input);

	// copying console_input into msg with length of console_input + 1
	memcpy(msg, handler_args->console_input, sendbytes+1);
	
	 // write to server
    if(write(sock, msg, sendbytes) != sendbytes)
		printf("write error\n");


	// exit function
	// free message in handler args
	// close socket
	close(sock);

	pthread_exit(NULL);
}

void* join_server(void* _handler_args)
{
	// capture properties file, this should be the third arg

	// check for invalid properties file

	// check for console input being longer then JOIN

		// parse and capture the ip_addr

		// check for invalid ip_addr

			// back and ask for valid input

		// parse and capture the port

			// back and ask for valid input

		// set port to port from ____.properties

		// set ip_addr to id_addr from ____.properties

	// otherwise use the default values

		// use defines to grab default IP

		// use defines to grab default port

	// should set a flag of some sort so the user can't rejoin if they are already joined

	// stub return
	return 0;
}

int command_read(char* input_string)
{
	char *command_string;
	char *second_string;

	int command_num;

	// parse input_string for the command

	// captures the first string which should be a command
	command_string = strtok_r(input_string, " ", &input_string);

	// compare the command_string to possible commands
	// check for join command
	if (strcmp(command_string, "JOIN\n") == 0)
	{
		command_num = JOIN;
	}

	// otherwise check for leave command
	else if (strcmp(command_string, "LEAVE\n") == 0)
	{
		command_num = LEAVE;
	}

	// otherwise check for shutdown command with and with out newline
	else if (strcmp(command_string, "SHUTDOWN\n") == 0 || 
			 strcmp(command_string, "SHUTDOWN") == 0)
	{
		command_num = SHUTDOWN;

		// check to see if the next token is "all"
		second_string = strtok_r(input_string, " ", &input_string);

		// check that the second_string isn't null ( this is to avoid comparing test_string with
		// NULL and giving us a seg fault)
		if (second_string != NULL)
		{
			// if it is, change the command string to SHUTDOWN ALL
			if (strcmp(second_string, "ALL\n") == 0)
			{
				command_num = SHUTDOWN_ALL;
			}
		}
		

	}

	// otherwise assume note
	else
	{
		command_num = NOTE;
	}
	// return the number associated with the enum command
	return command_num;
}


