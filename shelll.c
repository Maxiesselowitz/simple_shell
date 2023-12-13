#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void execute_command(char *command) {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        if (execlp(command, command, (char *)NULL) == -1) {
            perror("execlp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            printf("($)\n");
        }
    }
}

void interactive_mode() {
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("($) ");
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            // Handle end of file (Ctrl+D)
            printf("\n");
            break;
        }

        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0) {
            break;
        }

        execute_command(buffer);
    }
}

void non_interactive_mode(FILE *input) {
    char buffer[BUFFER_SIZE];

    while (fgets(buffer, BUFFER_SIZE, input) != NULL) {
        // Remove newline character
        buffer[strcspn(buffer, "\n")] = '\0';
        execute_command(buffer);
    }
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

