#include "message.h"


/* global variables */


/* function implementation */
void read_message(struct message* _msg, int _sock)
{
	read(_sock, &_msg->type, sizeof(uint8_t));
	read_complete(_sock, &_msg->port, sizeof(int));
	read_complete(_sock, &_msg->ip_addr, sizeof(unsigned int));

	read_note(_msg->note, _sock);
}

void read_note(struct note* _note, int _sock)
{
	read(_sock, &_note->username, sizeof(char) * LEN_USERNAME);
	read(_sock, &_note->sentence, sizeof(char) * LEN_SENTENCE);
	read_complete(_sock, &_note->length, sizeof(uint8_t));
}

void write_message(struct message* _msg, int _sock)
{
	write(_sock, &_msg->type, sizeof(uint8_t));
	write(_sock, &_msg->port, sizeof(int));
	write(_sock, &_msg->ip_addr, sizeof(unsigned int));

	write_note(_msg->note, _sock);
}

void write_note(struct note* _note, int _sock)
{
	write(_sock, &_note->username, sizeof(char) * LEN_USERNAME);
	write(_sock, &_note->sentence, sizeof(char) * LEN_SENTENCE);
	write(_sock, &_note->length, sizeof(uint8_t));
}

