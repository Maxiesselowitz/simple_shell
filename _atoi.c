#include "shell.h"

/**
 * interactive - it returns true if shell is interactive
 *
 * @info: the struct address
 *
 * Return: 1 if interactive mode and 0 if not
 */

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - it checks if character is a delimeter
 *
 * @c: the char to check
 *
 * @delim: the delimeter string
 *
 * Return: 1 if true and 0 if false
 */

int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);

	return (0);
}

/**
 * _isalpha - it checks for alphabetic character
 *
 * @c: the character to input
 *
 * Return: 1 if c is alphabet, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z' || (c >= 'A' && c <= 'Z')))
		return (1);

	else
		return (0);
}

/**
 * _atoi - converts a string to an interger
 *
 * @s: the string to convert
 *
 * Return: 0 if string contains no number and 1 otherwise
 */

int _atoi(char *s)
{
	int i, sign = i, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[i] - '0');
		}

		else if (flag == -1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;

	else
		output = result;

	return (output);
}
