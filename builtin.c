#include "shell.h"

/**
 * _myexit - it exits the shell
 *
 * @info: the structure that contains argument
 *
 * Return: it exit with a given status
 */

int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1]) /* if an arguemnt exist*/
	{
		exitcheck = _erratoi(info->argv[1]);

		if (exitcheck == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');

			return (1);
		}

		info->err_num = erratoi(info->argv[1]);
		return (-2);
	}
}

/**
 * _mycd - it changes the current directory of the process
 *
 * @info: the structure that contains the arguments
 *
 * Return: Always 0
 */

int _mycd(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == 1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1], _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - it changes the current directory of the process
 *
 * @info: it contains the potential argument
 *
 * Return: Always 0
 */

int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv
		_puts("help call works. Function not yet printed \n");

	if (0)
		_puts(*arg_array); /* temporary att_unsed work around */
	return (0);
}
