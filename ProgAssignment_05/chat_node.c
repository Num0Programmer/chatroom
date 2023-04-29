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

void remove_chat_node(struct chat_node_list* _list, unsigned int _ip_addr)
{
	struct chat_node* remove_node = _list->head;

	if (_list->head != NULL && remove_node->ip_addr == _ip_addr)
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
			if (wrk_node->next_node->ip_addr == _ip_addr)
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

