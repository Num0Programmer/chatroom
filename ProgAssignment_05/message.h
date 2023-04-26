#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#ifndef MESSAGE_H
#define MESSAGE_H


/* structures */
struct note
{
	char username[16];
	char sentence[64];
	uint8_t length;
};

struct message
{
	uint8_t type;
	uint8_t ip_addr[4];
	int port;
	struct note* note;
};


/* enums and externs */
enum types
{
	NOTE,
	JOIN,
	LEAVE,
	SHUTDOWN,
	SHUTDOWN_ALL
};


/* function prototypes */
void default_message(struct message* _msg);
void default_note(struct note* _note);

void message_init(
	struct message* _msg,
	uint8_t _type,
	uint8_t _ip_addr[4],
	int _port,
	struct note* _note
);

void note_init(
	struct note* _note,
	char* _username,
	char* _sentence,
	uint8_t _len
);

void read_message(struct message* _msg, int _sock);
void read_note(struct note* _note, int _sock);
void write_message(struct message* _msg, int _sock);
void write_note(struct note* _note, int _sock);
int read_int(int* int_ptr, int _sock);
int command_read(char* input_string);


/* preprocessor definitions */


#endif /* MESSAGE_H */

