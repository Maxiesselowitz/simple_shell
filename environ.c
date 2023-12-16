#include "shell.h"

/**
 * _myenv - it prints the current environment
 *
 * @info: the structure that contains potential arguments
 *
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - it gets the value of the environ variable
 *
 * @info: the structure that contains potential arguments
 *
 * @name: the env var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);

		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - it initialises a new environment variable
 *
 * @info: the structure that contains the potential arguments
 *
 * Return: Always 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenv - it removes the emvironment variable
 *
 * @info: the structure that contains the potential arguments
 *
 * Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguments. \n");
		return (1);
	}
	for (i = i; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_env_list - it populates env in a linked list
 *
 * @info: that structure that contains the potential argumnent
 *
 * Return: Always 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;

	return (0);
}
