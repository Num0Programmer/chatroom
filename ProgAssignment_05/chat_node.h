#include <stdio.h>
#include <stdlib.h>

#include "message.h"


#ifndef CHAT_NODE_H
#define CHAT_NODE_H


/* structures */
struct chat_node
{
	char* ip_addr;
	int port;
	struct chat_node* next_node;
};

struct chat_node_list
{
	size_t size;
	struct chat_node* head;
};


/* enums and externs */


/* function prototypes */
void add_chat_node(struct chat_node_list* _list, struct chat_node* _node);
void chat_node_init(struct chat_node* _node, char* _ip_addr, int _port);
void chat_node_list_init(struct chat_node_list* _list);
void destroy_chat_node_list(struct chat_node_list* _list);
void remove_chat_node(struct chat_node_list* _list, char* _ip_addr);


/* preprocessor definitions */


#endif /* CHAT_NODE_H */

