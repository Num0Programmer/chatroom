#include "main.h"

// Should handle the connection with the server. One main loop to handle incoming requests and 
// out going messages/commands. 

/* global variables */
pthread_mutex_t mutex;


int main(int argc, char** argv)
{
	// define thread information
	pthread_t receiver_thread;
	pthread_mutex_init(&mutex, NULL);
	// define funciton handler arguments
	struct handler_args* ha = (struct handler_args*)malloc(
		sizeof(struct handler_args)
	);

	// initialize client input c-string
	int msg_type;
	char client_input[MAX_CHARS];
	char *props_name = argv[1];

	// check if a properties file was given
	if (props_name == NULL)
	{
		perror("Error no properties file");
		exit(EXIT_FAILURE);
	}

	// initialize handler args
	ha->mutex = &mutex;
	ha->connected = FALSE;
	ha->props_str = malloc(strlen(props_name) + 1);
	ha->msg = (struct message*)malloc(sizeof(struct message));
	ha->msg->note = (struct note*)malloc(sizeof(struct note));

	memset(ha->msg->note->username, 0, LEN_USERNAME);
	memcpy(ha->props_str, props_name, strlen(props_name) + 1);

	load_props(ha);

	// zero out clint_input
	memset(client_input, 0, MAX_CHARS);
	// while chatting code is not equal to SHUTDOWN
	while (msg_type != SHUTDOWN || msg_type != SHUTDOWN_ALL)
	{
		// zero out clint_input
		memset(client_input, 0, MAX_CHARS);
		memset(ha->msg->note->sentence, 0, LEN_SENTENCE);

		// capture input from command line
		fgets(client_input, MAX_CHARS, stdin);

		// extract client input ha
		if ((msg_type = command_read(client_input)) != JOIN && !ha->connected)
		{
			print_join_help();
			continue;
		}

		// switch according to msg_type
		switch(msg_type)
		{
			case JOIN:
				join_room(ha, client_input);
				char sentence[LEN_SENTENCE] = "Request to join room!";
				ha->msg->type = JOIN;
				ha->msg->port = ha->port;
				ha->msg->ip_addr = ip_pton(ha->ip_addr);

				strcpy(ha->msg->note->sentence, sentence);
				printf("In sentence: %s\n", ha->msg->note->sentence);
				ha->msg->note->length = 21;

				if (pthread_create(
						&receiver_thread, NULL,
						receiver_handler, (void*)&ha->port
					) != 0
				)
				{
					perror("Error failure creating receiver thread");
					exit(EXIT_FAILURE);
				}

				ha->connected = TRUE;
				break;

			case LEAVE:
				if (pthread_cancel(receiver_thread) == -1)
				{
					perror("Error canceling receiver thread");
					exit(EXIT_FAILURE);
				}
				ha->connected = FALSE;
				break;

			case SHUTDOWN:
				break;

			case SHUTDOWN_ALL:
				break;

			default:	// assume NOTE
				sscanf(client_input, "%s", ha->msg->note->sentence);
				break;
		}

		// start sender thread - hand message to send
		pthread_t send_thread;
		if (pthread_create(&send_thread, NULL, sender_handler, (void*)ha) != 0)
		{
			perror("Error failure creating sender thread");
			exit(EXIT_FAILURE);
		}
		
		// check detach sender thread
		if (pthread_detach(send_thread) != 0)
		{
			perror("Error detaching thread");
			exit(EXIT_FAILURE);
		}

		pthread_mutex_lock(&mutex);
	}

	// exit program
	pthread_mutex_destroy(&mutex);
	return EXIT_SUCCESS;
}


/* function implementation */
int command_read(char* input_string)
{
	char *cpy_in_str = NULL;
	char *command_string = NULL;
	char *second_string= NULL;

	int command_num;

	cpy_in_str = malloc(sizeof(char) * (strlen(input_string) + 1));

	// copy console_input in order to not delete anything
    strcpy(cpy_in_str, input_string);

	// captures the first string which should be a command
	command_string = strtok_r(cpy_in_str, " ", &cpy_in_str);

	// check if last char is newline
	if (command_string[strlen(command_string) - 1] == '\n')
	{
		// replace lastchar with \0
		command_string[strlen(command_string) - 1] = '\0';
	}
	
	// compare the command_string to possible commands
	// check for join command
	if (strcmp(command_string, "JOIN\0") == 0)
	{
		command_num = JOIN;
	}
	// otherwise check for leave command
	else if (strcmp(command_string, "LEAVE\0") == 0)
	{
		command_num = LEAVE;
	}
	// otherwise check for shutdown command with and with out newline
	else if (
		strcmp(command_string, "SHUTDOWN\0") == 0
		|| strcmp(command_string, "SHUTDOWN") == 0
	)
	{
		command_num = SHUTDOWN;

		// check to see if the next token is "all"
		second_string = strtok_r(input_string, " ", &input_string);

		// check that the second_string isn't null ( this is to avoid comparing test_string with
		// NULL and giving us a seg fault)
		if (second_string != NULL)
		{
			// if it is, change the command string to SHUTDOWN ALL
			if (strcmp(second_string, "ALL\0") == 0)
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

/*
Unsure of what to do with this function atm, or if we really need it now
*/
void* join_room(void* _handler_args, char* input_string)
{
	int cmd_len = 0;
	int default_join_len = 5;
	char* cpy_con_in = NULL;
	char* dest_ip_str = NULL;
	char* dest_port_str = NULL;
	char* cmd_str = NULL;
	struct handler_args* handler_args = (struct handler_args*)_handler_args;

	// malloc space for cpy_con_in
	cpy_con_in = malloc(sizeof(char) * (strlen(input_string) + 1));

	// copy console input
	strcpy(cpy_con_in, input_string);

	// find command string length
	cmd_len = strlen(input_string);

	// parsing to get back cmd str, cmd_str won't be used
	cmd_str = strtok_r(cpy_con_in, " ", &cpy_con_in);

	// check for console input being longer then JOIN
	if (cmd_len > default_join_len)
	{
		// parse and capture the ip_addr
		dest_ip_str = strtok_r(cpy_con_in, " ", &cpy_con_in);

		// parse and capture the port
		dest_port_str = strtok_r(cpy_con_in, " ", &cpy_con_in);

		// set port to handler_args dest_port, this overwrites the default
		handler_args->dest_ip_addr = dest_ip_str;

		// set ip_addr to handler_args dest_ip_addr, this overwrites the default
		handler_args->dest_port = atoi(dest_port_str);
	}
	// otherwise, assume joining default room
	else
	{
		load_props(handler_args);
	}

	// stub return
	return 0;
}

/*
desc: grabs properties from the ___.properties file and loads them into the handler_args
params: *handler_args
returns: void* with handler_args loaded with props 
*/
void load_props(struct handler_args* _handler_args)
{
	// grab properties
	char* properties_file = NULL;
    Properties* properties;
	char* value;
    char* key = "MY_PORT";

	properties_file = malloc(sizeof(char) * (strlen(_handler_args->props_str) + 1));

	// inject properties_file with the properties file string to use
	strcpy(properties_file, _handler_args->props_str);

	// grabbing MY_PORT value from ___.properties
    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);
    
	// turning port from string to int
		// method: atoi()
	_handler_args->port = atoi(value);

	// grabbing IP address from ___.properties
    key = "MY_IP";

    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

	_handler_args->ip_addr = malloc(strlen(value) + 1);

	memcpy(_handler_args->ip_addr, value, strlen(value) + 1);

	// grabbing IP address from ___.properties
	key = "DEST_PORT";

	// grabbing MY_PORT value from ___.properties
    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

	// turning port from string to int
		// method: atoi()
	_handler_args->dest_port = atoi(value);

	// grabbing DEST_IP address from ___.properties
    key = "DEST_IP";

    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

	_handler_args->dest_ip_addr = malloc(strlen(value) + 1);

	memcpy(_handler_args->dest_ip_addr, value, strlen(value) + 1);

	// grabbing USER_NAME from ____.properties
	key = "USER_NAME";

    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

	strcpy(_handler_args->msg->note->username, value);
}

void print_join_help()
{
	printf("Please connect to a room:\n");
	printf("JOIN - the default room in *.properties\n");
	printf("JOIN <ip address> <port> - a specific room\n\n");
}

