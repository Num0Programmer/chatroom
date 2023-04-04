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
enum types
{
	NOTE,
	JOIN,
	LEAVE,
	SHUTDOWN,
	SHUTDOWN_ALL
};


/* function prototypes */
void add_chat_node(struct chat_node_list* _list, struct chat_node* _node);
void chat_node_init(struct chat_node* _node, size_t _ip_addr, int _port);
void chat_node_list_init(struct chat_node_list* _list);
void remove_chat_node(struct chat_node_list* _list, size_t _ip_addr);


/* preprocessor definitions */


#endif /* CHAT_NODE_H */

