#include "shell.h"

/**
 * hsh - the main shell loop
 *
 * @info: the parameter & return info
 *
 * @av: the argument vector from main
 *
 * Return: 0 om success, 1 on error
 */

int hsh(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);

		r = get_input(info);

		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find _builtin(info);

			if (builtin_ret == -1)
				find_cmd(info);
		}

		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}

	write_history(info);
	free_info(info, 1);

	if (!interactive(info) && info->status)
		exit(info->status);

	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(inf0->err_num);
	}

	return (builtin_ret);
}

/**
 * find_builtin - it finds a builtin command
 *
 * @info: the parameter
 *
 * Return: -1 if not found
 */

int find_builtin(info_t *info)
{
	int i, builtin_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);

			return (built_in_ret);
		}
}

/**
 * find_cmd - finds a command
 *
 * @info: the parameter
 *
 * Return: void
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];

	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}

	for (i = 0; k = 0; info ->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;

	if (!k)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0];
			
			if (path) 
			{
				INFO->PATH = PATH;'
				Fork_cmd(info);
			}
			else
