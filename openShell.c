#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 100

// Function to execute a shell command
void executeCommand(const char *command) {
    system(command);
}

int main() {
    char input[MAX_INPUT_LENGTH];

    while (1) {
        printf("SimpleShell> ");
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Exit the program if the user enters "exit"
        if (strcmp(input, "exit") == 0) {
            printf("Exiting the shell program...\n");
            break;
        }

        // Execute the entered command
        executeCommand(input);
    }

    return 0;
}