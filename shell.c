#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
    printf("($) ");
}

/**
 * read_command - Read a command from the user.
 *
 * Return: A pointer to the read command.
 */
char *read_command(void)
{
    char *command = NULL;
    size_t bufsize = 0;

    if (getline(&command, &bufsize, stdin) == -1) {
        if (feof(stdin)) {
            printf("\n");
            exit(EXIT_SUCCESS);
        } else {
            perror("getline");
            exit(EXIT_FAILURE);
        }
    }

    return command;
}

/**
 * execute_command - Execute a command.
 *
 * @command: The command to execute.
 */
void execute_command(char *command)
{
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {

        if (execve(command, NULL, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else {

        do {
            wpid = waitpid(pid, &status, WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

int main(void)
{
	char *command;

	while (1) {
	display_prompt();
	command = read_command();

	if (command[strlen(command) - 1] == '\n') {
		command[strlen(command) - 1] = '\0';
	}

	execute_command(command);

	free(command);
}
	return 0;
}
