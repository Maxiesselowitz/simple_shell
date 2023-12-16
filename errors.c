#include "shell.h"

/**
 * _eputs - it prints an input string
 *
 * @str: the string to print
 *
 * Return: void
 */

void _eputs(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
		_eputschar(str[i]);
		i++;
	}
}

/**
 * _eputschar - it writes the character c to stderr
 *
 * @c: the character to print
 *
 * Return: 1 on success
 */

int _eputschar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putfd - it writes the character to c to given fd
 *
 * @c: the character to print
 *
 * @fd: the file description to write
 *
 * Return: 1 on success
 */

int _putfd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}

	if (c != BUF_FLUSH)
		buf[i++] = c;

	return (1);
}

/**
 * _putsfd - it prints an input string
 *
 * @str: the string to be printed
 *
 * @fd: the file description to write
 *
 * Return: the number of chars to put
 */

int _putsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);

	while (*str)
	{
		i += _putfd(*str++, fd);
	}

	return (i);
}
