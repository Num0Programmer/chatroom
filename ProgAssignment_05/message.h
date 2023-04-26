#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>


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
	char* ip_addr;
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
int command_read(char* input_string);
void print_note(struct note* _note);
int read_int(int* int_ptr, int _sock);
void read_message(struct message* _msg, int _sock);
void read_note(struct note* _note, int _sock);
void write_message(struct message* _msg, int _sock);
void write_note(struct note* _note, int _sock);


/* preprocessor definitions */


#endif /* MESSAGE_H */

