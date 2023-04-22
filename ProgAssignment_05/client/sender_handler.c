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
	
	// define message construction variables
	struct message msg;

	// capture command
	command = command_read(handler_args->console_input);
	
	// switch based on command
	switch (command)
	{
		case JOIN:
			printf("join command\n");
			join_server(handler_args);
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
	msg.type = command;
	msg.port = handler_args->port;
	memcpy(msg.ip_addr, handler_args->ip_addr, sizeof(strlen(handler_args->ip_addr) + 1));

	printf("%d\n", handler_args->port);

	// filling in socket info
	sock = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(handler_args->ip_addr);
    server_addr.sin_port = htons(23657);

	// unlock mutex
    
	// connect to socket
   if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
		// report socket creation error
        printf("Error: connection unsuccessful!\n");
		// exit program
        exit(EXIT_FAILURE);
    }

	 // write to server
    if(write(sock, &msg, sizeof(msg)) != sizeof(struct message))
		printf("write error\n");

	// exit function
	// free message in handler args
	// close socket
	close(sock);

	pthread_exit(NULL);
}

void* join_server(void* _handler_args)
{
	printf("join server\n");
	// capture properties file, this should be the third arg
	
	// loads props into handler_args
	load_props(_handler_args);

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

/*
desc: grabs properties from the ___.properties file and loads them into the handler_args
params: *handler_args
returns: void* with handler_args loaded with props 
*/
void load_props(struct handler_args* handler_args)
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
	handler_args->port = atoi(value);

	// grabbing IP address from ___.properties
    key = "MY_IP";

    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

	handler_args->ip_addr = malloc(strlen(value) + 1);

	memcpy(handler_args->ip_addr, value, strlen(value) + 1);
	printf("%s\n", handler_args->ip_addr);

	// grabbing IP address from ___.properties
	key = "DEST_PORT";

	// grabbing MY_PORT value from ___.properties
    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);
    
	// turning port from string to int
		// method: atoi()
	handler_args->dest_port = atoi(value);

	// grabbing DEST_IP address from ___.properties
    key = "DEST_IP";

    properties = property_read_properties(properties_file);
    value = property_get_property(properties, key);

	handler_args->dest_ip_addr = malloc(strlen(value) + 1);

	memcpy(handler_args->dest_ip_addr, value, strlen(value) + 1);
	printf("%s\n", handler_args->dest_ip_addr);

	
}



