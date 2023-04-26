#include "message.h"


/* global variables */


/* function implementation */
void read_message(struct message* _msg, int _sock)
{
	read(_sock, &_msg->type, sizeof(uint8_t));
	read_int(&_msg->port, _sock);
	read_note(_msg->note, _sock);

	// honor byte order
	_msg->ip_addr[0] = htonl(_msg->ip_addr[0]);
	_msg->ip_addr[1] = htonl(_msg->ip_addr[1]);
	_msg->ip_addr[2] = htonl(_msg->ip_addr[2]);
	_msg->ip_addr[3] = htonl(_msg->ip_addr[3]);
	// read ip address to socket
	read(_sock, &_msg->ip_addr[0], sizeof(uint8_t));
	read(_sock, &_msg->ip_addr[1], sizeof(uint8_t));
	read(_sock, &_msg->ip_addr[2], sizeof(uint8_t));
	read(_sock, &_msg->ip_addr[3], sizeof(uint8_t));
}

void read_note(struct note* _note, int _sock)
{
	read(_sock, &_note->username, sizeof(char) * 16);
	read(_sock, &_note->sentence, sizeof(char) * 64);
	_note->length = htonl(_note->length);
	read(_sock, &_note->length, sizeof(uint8_t));
}

void write_message(struct message* _msg, int _sock)
{
	write(_sock, &_msg->type, sizeof(uint8_t));
	write(_sock, &_msg->port, sizeof(uint8_t));	

	// write ip address to socket
	write(_sock, &_msg->ip_addr[0], sizeof(uint8_t));
	write(_sock, &_msg->ip_addr[1], sizeof(uint8_t));
	write(_sock, &_msg->ip_addr[2], sizeof(uint8_t));
	write(_sock, &_msg->ip_addr[3], sizeof(uint8_t));
	// honoring network byte order
	_msg->ip_addr[0] = ntohl(_msg->ip_addr[0]);
	_msg->ip_addr[1] = ntohl(_msg->ip_addr[1]);
	_msg->ip_addr[2] = ntohl(_msg->ip_addr[2]);
	_msg->ip_addr[3] = ntohl(_msg->ip_addr[3]);

	write_note(_msg->note, _sock);
}

void write_note(struct note* _note, int _sock)
{
	write(_sock, &_note->username, sizeof(char) * 16);
	write(_sock, &_note->sentence, sizeof(char) * 64);
	write(_sock, &_note->length, sizeof(uint8_t));
	_note->length = ntohl(_note->length);
}

int read_int(int* int_ptr, int _sock)
{
    int bytes_read;

    for (int bytes_left = 4; bytes_left > 0; bytes_left -= bytes_read)
    {
        bytes_read = read(_sock, int_ptr, sizeof(int));

        if (bytes_read == 4)
        {
            break;  // all bytes read in one go
        }
        else if (bytes_read == -1)
        {
            break;  // problem in network
        }

        *int_ptr <<= (bytes_left - bytes_read) * 8;
    }

    return 4;
}

int command_read(char* input_string)
{
	char *cpy_in_str = NULL;
	char *command_string = NULL;
	char *second_string= NULL;

	int command_num;

	cpy_in_str = malloc(sizeof(char) * (strlen(input_string) + 1));

	// copy input_string in order to not delete anything
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
	else if (strcmp(command_string, "SHUTDOWN\0") == 0 || 
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

