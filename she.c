#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void execute_command(char *command) {
    pid_t child_pid, wpid;
    int status;

    child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        char *args[] = {command, NULL};
        if (execve(command, args, NULL) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        do {
            wpid = waitpid(child_pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void interactive_mode() {
    char *line = NULL;
    size_t len = 0;

    while (1) {
        printf("($) ");
        if (getline(&line, &len, stdin) == -1) {
            break; // Exit on EOF or error
        }

        // Remove newline character
        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") == 0) {
            break;
        }

        execute_command(line);
    }

    free(line);
}

void non_interactive_mode(FILE *input) {
    char *line = NULL;
    size_t len = 0;

    while (getline(&line, &len, input) != -1) {
        // Remove newline character
        line[strcspn(line, "\n")] = '\0';
        execute_command(line);
    }

    free(line);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Interactive mode
        interactive_mode();
    } else if (argc == 2) {
        // Non-interactive mode
        FILE *input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        non_interactive_mode(input);
        fclose(input);
    } else {
        fprintf(stderr, "Usage: %s [script]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    return 0;
}

