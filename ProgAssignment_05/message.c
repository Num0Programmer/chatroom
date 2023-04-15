#include "message.h"


/* global variables */

/*

struct message* default_message(void)
{
	struct message* m = (struct message*)malloc(sizeof(struct message));
	
	m->type = NOTE;
	m->ip_addr[0] = 0;
	m->ip_addr[1] = 0;
	m->ip_addr[2] = 0;
	m->ip_addr[3] = 0;
	m->port = 0;
	m->note = default_note();

	return m;
}

struct note* default_note(void)
{
	struct note* n = (struct note*)malloc(sizeof(struct note));
	
	n->length = 0;
	
	return n;
}
*/
struct message* message_init(uint8_t _type, uint8_t* _ip_addr, int _port, struct note* _node)
{
	// allocate new memory for a message

	// set type to incoming type
	// set ip address to incoming ip address
	// set port to incoming port
	// set note to incoming note
	
	// return message pointer
	return NULL;
}

struct note* note_init(char* _username, char* _sentence, uint8_t _len)
{
	// allocate new memory for a note

	// set username to incoming username
	// set sentence to incoming sentence
	// set length to incoming length
	
	// return note pointer
	return NULL;
}

void read_message(struct message* _message)
{
	// read message type to socket
	// read ip address to socket
	// read port to socket
	// read note
}

void read_note(struct note* _note, int _sock)
{
	// read username to socket
	// read sentence to socket
	// read length to socket
}

void write_message(struct message* _message)
{
	// write message type to socket
	// write ip address to socket
	// write port to socket
	// write note
}

void write_note(struct note* _note, int _sock)
{
	// write username to socket
	// write sentence to socket
	// write length to socket
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

