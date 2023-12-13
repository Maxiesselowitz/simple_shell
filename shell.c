#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * execute_command - it executes a command
 *
 * @command: the input to execute
 *
 * Return: ($)
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{

		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execlp(command, command, (char *)NULL) == -1)
		{
			perror("execlp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			printf("($)\n");
		}
	}
}

/**
 * interactive_mode - it receives command
 *
 */

void interactive_mode(void)
{

	char buffer[BUFFER_SIZE];

	while (1)
	{
		printf("($) ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		buffer[strcspn(buffer, "\n")] = '\0';

		if (strcmp(buffer, "exit") == 0)
		{
			break;
		}
		execute_command(buffer);
	}
}

/**
 * non_interactive_mode - it displays result
 *
 * @input: the input
 */

void non_interactive_mode(FILE *input)
{
	char buffer[BUFFER_SIZE];

	while (fgets(buffer, BUFFER_SIZE, input) != NULL)
	{
		buffer[strcspn(buffer, "\n")] = '\0';
		execute_command(buffer);
	}
}

/**
 * main - it prints interactive and non-interactive modes
 *
 * @argc: the arguments
 *
 * @argv: the array
 *
 * Return: Always 0
 */

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		interactive_mode();
	}
	else if (argc == 2)
	{
		FILE *input = fopen(argv[1], "r");

		if (input == NULL)
		{
			perror("fopen");
			exit(EXIT_FAILURE);
		}
		non_interactive_mode(input);
		fclose(input);
	}
	else
	{
		fprintf(stderr, "Usage: %s [script]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}
