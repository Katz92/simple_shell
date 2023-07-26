#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (head == NULL)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (new_head == NULL)
		return (NULL);
	_memset((void *)new_head, nil, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (new_head->str == NULL)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (head == NULL)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (new_node == NULL)
		return (NULL);
	_memset((void *)new_node, nil, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (new_node->str == NULL)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t index = nil;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		index++;
	}
	return (index);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = nil;

	if (head == NULL || *head == NULL)
		return (nil);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (solo);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (solo);
		}
		i++;
		prev_node = node;
		node = node->next;
	}
	return (nil);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *n_node, *head;

	if (head_ptr == NULL || *head_ptr == NULL)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		n_node = node->next;
		free(node->str);
		free(node);
		node = n_node;
	}
	*head_ptr = NULL;
}
