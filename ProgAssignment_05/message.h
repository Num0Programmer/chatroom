#include <stdlib.h>
#include <string.h>


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
	struct note note;
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
struct message* default_message(void);
struct note* default_note(void);
struct message* message_init(uint8_t _type, uint8_t* _ip_addr, int _port, struct note* _node);
struct note* note_init(char* _username, char* _sentence, uint8_t _len);
void read_message(struct message* _message);
void read_note(struct note* _note, int _sock);
void write_message(struct message* _message);
void write_note(struct note* _note, int _sock);
int command_read(char* input_string);



/* preprocessor definitions */


#endif /* MESSAGE_H */

