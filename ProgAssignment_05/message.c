#include "message.h"


/* global variables */


/* function implementation */
void message_init(struct message* _message, uint8_t _type, size_t _ip_addr, int _port, struct note* _node)
{
	// set type to incoming type
	// set ip address to incoming ip address
	// set port to incoming port
	// set note to incoming note
}

void note_init(struct note* _note, char* _username, char* _sentence, uint8_t _len)
{
	// set username to incoming username
	// set sentence to incoming sentence
	// set length to incoming length
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

