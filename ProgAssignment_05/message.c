#include "message.h"


/* global variables */


/* function implementation */
struct message* default_message()
{
	// return pointer to anonymous message
	return (struct message*)malloc(sizeof(struct message));
}

struct note* default_note()
{
	// return pointer to anonymous note
	return (struct note*)malloc(sizeof(struct note));
}

struct message* message_init(uint8_t _type, size_t _ip_addr, int _port, struct note* _node)
{
	// allocate new memory for a message

	// set type to incoming type
	// set ip address to incoming ip address
	// set port to incoming port
	// set note to incoming note
	
	// return message pointer
}

struct note* note_init(char* _username, char* _sentence, uint8_t _len)
{
	// allocate new memory for a note

	// set username to incoming username
	// set sentence to incoming sentence
	// set length to incoming length
	
	// return note pointer
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

