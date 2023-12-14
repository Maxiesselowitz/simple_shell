#include "shell.h"

/**
 * main - the main funtion
 *
 * @ac: the count of the arguments
 *
 * @argv: the arguments
 *
 * Return: 0 Always (success)
 */

int main(int ac, char **argv)
{
	char *line = NULL;

	int status = 0;
	(void) ac;
	(void) argv;

	while (1)
	{
		line = read_line();
		if (line == NULL)
			return (status);

		printf("%s", line);

	}

}
