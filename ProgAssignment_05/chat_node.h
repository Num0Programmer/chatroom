#include <stdlib.h>

#include "message.h"


#ifndef CHAT_NODE_H
#define CHAT_NODE_H


/* structures */
struct message
{
	uint8_t type;
	size_t ip_addr;
	int port;
	struct note* n;
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
void message_init(struct message* msg);


/* preprocessor definitions */


#endif /* CHAT_NODE_H */

