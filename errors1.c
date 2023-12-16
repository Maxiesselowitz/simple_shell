#include "shell.h"

/**
 * _errtoi - it converts a string into an integer
 *
 * @s: the string to be converted
 *
 * Return: 0 if there is no number in string, 1 otherwise
 */

int  _errtoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++; /* TODO: why does this make main return 2555? */

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - it prints an error message
 *
 * @info: the parameter and return info structure
 *
 * @estr: the string that contains the error type
 *
 * Return: 0 if no numbers in string and 1 if otherwise
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - the function that prints a decimal number (base 10)
 *
 * @input: the input
 *
 * @fd: the file description to write to
 *
 * Return: nnumber of characters that was printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;

	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;

	for (i = 1000000000; i > 1; i /= 10)
	{
		if _(abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}

	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - it converts a function
 *
 * @num: the number
 *
 * @base: the base
 *
 * @flags: the argument flags
 *
 * Return: the string
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}

	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	}

	while (n != 0);

	if (sign)
		* --ptr = sign;

	return (ptr);
}

/**
 * remove_comments - a function that replaces the first instance
 * '#' with '\0'
 *
 * @buf: the address of the string to change
 *
 * Return: Alawys 0
 */

void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
