#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

#include "misc.h"


#ifndef MESSAGE_H
#define MESSAGE_H


/* preprocessor definitions */
#define LEN_USERNAME 16
#define LEN_SENTENCE 64


/* structures */
struct note
{
	char username[LEN_USERNAME];
	char sentence[LEN_SENTENCE];
	uint8_t length;
};

struct message
{
	uint8_t type;
	unsigned int ip_addr;
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
int read_int(int* int_ptr, int _sock);
void read_message(struct message* _msg, int _sock);
void read_note(struct note* _note, int _sock);
void write_message(struct message* _msg, int _sock);
void write_note(struct note* _note, int _sock);


#endif /* MESSAGE_H */

