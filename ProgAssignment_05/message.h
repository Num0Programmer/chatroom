#include <stdlib.h>


#ifndef MESSAGE_H
#define MESSAGE_H


/* structures */
struct message
{
	uint8_t type;
	uint8_t ip_addr[4];
	int port;
	struct note* note;
};

struct note
{
	char username[16];
	char sentence[64];
	uint8_t length;
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
struct message* default_message();
struct note* default_note();
struct message* message_init(uint8_t _type, uint8_t* _ip_addr, int _port, struct note* _node);
struct note* note_init(char* _username, char* _sentence, uint8_t _len);
void read_message(struct message* _message);
void read_note(struct note* _note, int _sock);
void write_message(struct message* _message);
void write_note(struct note* _note, int _sock);


/* preprocessor definitions */


#endif /* MESSAGE_H */

