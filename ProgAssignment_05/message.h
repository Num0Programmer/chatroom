#include <stdlib.h>


#ifndef MESSAGE_H
#define MESSAGE_H


/* structures */
struct message
{
	uint8_t type;
	size_t ip_addr;
	int port;
	struct note* note;
};

struct note
{
	char usernamen[16];
	char sentence[64];
	uint8_t length;
};


/* function prototypes */
void message_init(struct message* _message, uint8_t _type, size_t _ip_addr, int _port, struct note* _node);
void note_init(struct note* _note, char* _username, char* _sentence, uint8_t _len);


/* preprocessor definitions */


#endif /* MESSAGE_H */

