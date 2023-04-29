#include "message.h"


/* global variables */


/* function implementation */
void print_note(struct note* _note)
{
	printf("%s: %s\n", _note->username, _note->sentence);
}

void read_message(struct message* _msg, int _sock)
{
	printf("start of read\n");
	

	read(_sock, &_msg->type, sizeof(uint8_t));
	printf("reading msg type: %d\n", _msg->type);

	read_complete(_sock, &_msg->port, sizeof(int));
	printf("reading port: %d\n", _msg->port);

	read_complete(_sock, &_msg->ip_addr, sizeof(unsigned int));
	printf("reading ip addr: %d\n", _msg->ip_addr);

	read_note(_msg->note, _sock);
}

void read_note(struct note* _note, int _sock)
{
	read(_sock, &_note->username, sizeof(char) * 16);
	printf("reading note username: %s\n", _note->username);

	read(_sock, &_note->sentence, sizeof(char) * 64);
	printf("reading note sentence: %s\n", _note->sentence);

	read_complete(_sock, &_note->length, sizeof(uint8_t));
	printf("reading note length: %d\n", _note->length);

}

void write_message(struct message* _msg, int _sock)
{
	write(_sock, &_msg->type, sizeof(uint8_t));
	printf("writing msg type: %d\n",_msg->type );
	write(_sock, &_msg->port, sizeof(int));	
	printf("writing port : %d\n",_msg->port );
	write(_sock, &_msg->ip_addr, sizeof(unsigned int));
	printf("writing ip: %d\n",_msg->ip_addr );
	write_note(_msg->note, _sock);
}

void write_note(struct note* _note, int _sock)
{
	write(_sock, &_note->username, sizeof(char) * 16);
	printf("writing msg username: %s\n",_note->username );
	write(_sock, &_note->sentence, sizeof(char) * 64);
	printf("writing note sentence: %s\n",_note->sentence );
	write(_sock, &_note->length, sizeof(uint8_t));
	printf("writing note length: %d\n",_note->length );

}

