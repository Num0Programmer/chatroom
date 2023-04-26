#include "sender_handler.h"
 
// code responsible for 

/* global variables */


/* function implementation */
void* sender_handler(void* _handler_args)
{
	int sock;
	int command = 0;
	struct handler_args* handler_args = _handler_args;
    struct sockaddr_in server_addr;
	
	// define message construction variables
	struct message* msg = (struct message*)malloc(sizeof(struct message));
	msg->note = (struct note*)malloc(sizeof(struct note));

	// capture command
	command = command_read(handler_args->console_input);

	// switch based on command
	switch (command)
	{
		case JOIN:
			join_server(handler_args);
			strcpy(msg->note->username, "[default user]");
			strcpy(msg->note->sentence, "Hello to the server!");
			msg->note->length = (uint8_t)htonl(13);
			break;

		case LEAVE:
			printf("leave command\n");
			break;

		case SHUTDOWN:
			printf("shutdown command\n");
			break;

		case SHUTDOWN_ALL:
			printf("shutdown all command\n");
			break;
	
		default:
			printf("assumed note command\n");
			break;
	}

	// copying data in msg struct
	// Maybe make this into a function?
	msg->type = command;
	msg->port = handler_args->port;
	sscanf(
		handler_args->ip_addr, "%hhu.%hhu.%hhu.%hhu",
		&msg->ip_addr[0],
		&msg->ip_addr[1],
		&msg->ip_addr[2],
		&msg->ip_addr[3]
	);
	printf("message port: %d\n", msg->port);

	// filling in socket info
	sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(handler_args->dest_ip_addr);
    server_addr.sin_port = htons(handler_args->dest_port);

	// unlock mutex
	pthread_mutex_unlock(handler_args->mutex);

	// connect to socket
	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		// report socket creation error
        printf("Error connection unsuccessful");
        exit(EXIT_FAILURE);
    }

	// write to server
	write_message(msg, sock);

	// exit function
	close(sock);

	//terminate thread if not main thread
	pthread_exit(NULL);
}

/*
Unsure of what to do with this function atm, or if we really need it now
*/
void* join_server(void* _handler_args)
{
	int cmd_len = 0;
	int default_join_len = 5;
	char* cpy_con_in = NULL;
	char* dest_ip_str = NULL;
	char* dest_port_str = NULL;
	char* cmd_str = NULL;
	struct handler_args* handler_args = (struct handler_args*)_handler_args;

	// malloc space for cpy_con_in
	cpy_con_in = malloc(sizeof(char) * (strlen(handler_args->console_input) + 1));

	// copy console input
	strcpy(cpy_con_in, handler_args->console_input);
		
	// loads props into handler_args
	load_props(handler_args);

	// find command string length
	cmd_len = strlen(handler_args->console_input);

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
	// should set a flag of some sort so the user can't rejoin if they are already joined

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
	char* properties_file = "test.properties";
    Properties* properties;
	char* value;
    char* key = "MY_PORT";
    
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
}

