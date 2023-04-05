#include <stdlib.h>


#ifndef CHAT_NODE_H
#define CHAT_NODE_H


/* structures */
struct chat_node
{
	size_t ip_addr;
	int port;
	struct chat_node* node;
};

struct chat_node_list
{
	size_t size;
	struct chat_node* head;
};


/* enums and externs */


/* function prototypes */
void add_chat_node(struct chat_node_list* _list, struct chat_node* _node);
struct chat_node* chat_node_init(uint8_t* _ip_addr, int _port);
struct chat_node_list* chat_node_list_init(void);
void remove_chat_node(struct chat_node_list* _list, size_t _ip_addr);


/* preprocessor definitions */


#endif /* CHAT_NODE_H */

