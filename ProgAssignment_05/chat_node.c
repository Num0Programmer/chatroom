#include "chat_node.h"


/* global variables */


/* function implementation */
void message_init(struct message* msg)
{
	msg->type = NOTE;
	msg->ip_addr = 0;
	msg->port = 0;
	msg->n = NULL;
}

