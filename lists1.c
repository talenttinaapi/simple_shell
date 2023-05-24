#include "shell.h"
/**
 *list_len - ...
 *@h: ...
 *
 *Return: ...
 */
size_t list_len(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		h = h->next;
		k++;
	}
	return (k);
}

/**
 *list_to_strings - ...
 *@head: ...
 *
 *Return: ...
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t k = list_len(head), m;
	char **strs;
	char *str;

	if (!head || !k)
		return (NULL);
	strs = malloc(sizeof(char *) * (k + 1));
	if (!strs)
		return (NULL);
	for (k = 0; node; node = node->next, k++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (m = 0; m < k; m++)
				free(strs[m]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[k] = str;
	}
	strs[k] = NULL;
	return (strs);
}
/**
 *print_list - ...
 *@h: ...
 *
 *Return: ...
 */
size_t print_list(const list_t *h)
{
	size_t k = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		k++;
	}
	return (k);
}
/**
 *node_starts_with - ...
 *@node: ...
 *@prefix: ...
 *@c: ...
 *
 *Return: ...
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}
/**
 *get_node_index - ...
 *@head: ...
 *@node: ...
 *
 *Return: ...
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t k = 0;

	while (head)
	{
		if (head == node)
			return (k);
		head = head->next;
		k++;
	}
	return (-1);
}
