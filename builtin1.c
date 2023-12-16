#include "shell.h"

/**
 * _myhistory - it displays the history list
 *
 * @info: the structure that contains potential arguments
 *
 * Return: Always 0
 */

int _myhistory(infot_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - it sets alias to the string
 *
 * @info: the parameter struct
 *
 * @str: the string alias
 *
 * Return: 0 on success and 1 if fails
 */

int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	c = *p;
	*p = 0;

	ret = delete_node_at_index(&(info->alias);
			get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;

	return (ret);
}

/**
 * set_alias - it sets the alias to a string
 *
 * @info_t: the parameter struct
 *
 * @str: the string alias
 *
 * Return: 0 on success and 1 if fails
 */

int set_alias(info_t, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);

	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - it prints an alias to a string
 *
 * @node: the alias node
 *
 * Return: 0 on success and 1 if fail
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');

		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n'");

		return (0);
	}
	return (1);
}

/**
 * _myalias - it mimics the alias builtin
 *
 * @info: the structure with potential arguments
 *
 * Return: Always 0
 */

int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	lists_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);

		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}
	return (0);
}
