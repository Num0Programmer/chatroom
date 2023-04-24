#include "chat_node.h"


/* global variables */


/* function implementation */
void add_chat_node(struct chat_node_list* _list, struct chat_node* _node)
{
	// check list has data
	if (_list->size > 0)
	{
		// initialize working node with head
		struct chat_node* wrk_node = _list->head;

		// loop until last node is found
		while (wrk_node->next_node != NULL)
		{
			wrk_node = wrk_node->next_node;
		}

		// point last node's next pointer to incoming node
		wrk_node->next_node = _node;
	}
	// otherwise, assume list is empty
	else
	{
		_list->head = _node;
	}

	_list->size += 1;
}

void chat_node_init(struct chat_node* _node, uint8_t _ip_addr[4], int _port)
{
	_node = (struct chat_node*)malloc(sizeof(struct chat_node));

	// set port number to port
	_node->port = _port;
	
	// set ip address to ip_addr
	_node->ip_addr[0] = _ip_addr[0];
	_node->ip_addr[1] = _ip_addr[1];
	_node->ip_addr[2] = _ip_addr[2];
	_node->ip_addr[3] = _ip_addr[3];
}

void chat_node_list_init(struct chat_node_list* _list)
{
	_list = (struct chat_node_list*)malloc(sizeof(struct chat_node_list));

	_list->size = 0;
	_list->head = NULL;
}

void destroy_chat_node_list(struct chat_node_list* _list)
{
	struct chat_node* wrk_node = _list->head;
	struct chat_node* prev_node = wrk_node;

	// loop until previous node is NULL
	while (prev_node == NULL)
	{
		wrk_node = wrk_node->next_node;

		free(prev_node);

		prev_node = wrk_node;
	}

	free(_list);
}

void remove_chat_node(struct chat_node_list* _list, uint8_t _ip_addr[4])
{
	struct chat_node* remove_node = _list->head;

	if (_list->head != NULL
		&& (
			remove_node->ip_addr[0] == _ip_addr[0]
			&& remove_node->ip_addr[1] == _ip_addr[1]
			&& remove_node->ip_addr[2] == _ip_addr[2]
			&& remove_node->ip_addr[3] == _ip_addr[3]
		)
	)
	{
		_list->head = _list->head->next_node;
		free(remove_node);
		_list->size -= 1;
	}
	else if (_list->head != NULL)
	{
		// initialize working node with head node
		struct chat_node* wrk_node = remove_node;
		
		// loop until penultimate node found
		while (wrk_node->next_node != NULL)
		{
			// check next node's ip address equal to expected ip address
			if (
				wrk_node->next_node->ip_addr[0] == _ip_addr[0]
				&& wrk_node->next_node->ip_addr[1] == _ip_addr[1]
				&& wrk_node->next_node->ip_addr[2] == _ip_addr[2]
				&& wrk_node->next_node->ip_addr[3] == _ip_addr[3]
			)
			{
				remove_node = wrk_node->next_node;
				break;	// node to remove is found
			}

			wrk_node = wrk_node->next_node;
		}

		if (wrk_node != NULL)
		{
			wrk_node->next_node = wrk_node->next_node->next_node;
			free(remove_node);
			_list->size -= 1;
		}
	}
}

void write_to_chat_node_list(struct chat_node_list* _list, struct message* _msg)
{
	struct chat_node* wrk_node = _list->head;

	while (wrk_node != NULL)
	{
		write_message(_msg, wrk_node->port);

		wrk_node = wrk_node->next_node;
	}
}

