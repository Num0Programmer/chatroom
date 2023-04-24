#include <stdio.h>
#include <stdlib.h>

#include "message.h"


#ifndef CHAT_NODE_H
#define CHAT_NODE_H


/* structures */
struct chat_node
{
	uint8_t ip_addr[4];
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
void chat_node_init(struct chat_node* _node, uint8_t _ip_addr[4], int _port);
void chat_node_list_init(struct chat_node_list* _list);
void destroy_chat_node_list(struct chat_node_list* _list);
void remove_chat_node(struct chat_node_list* _list, uint8_t* _ip_addr);
void write_to_chat_node_list(struct chat_node_list* _list, struct message* _msg);


/* preprocessor definitions */


#endif /* CHAT_NODE_H */

