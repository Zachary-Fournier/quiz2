#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

char *custom_env[] = {"USER=Pikachu", "PATH=/tmp", NULL};

int main(void)
{
    pid_t first_child_pid, second_child_pid;
    int status;

    // Print the parent process PID
    printf("Running parent process PID: %d\n\n", getpid());

    // Fork the first child process
    first_child_pid = fork();

    if (first_child_pid == 0) { // First child process
        printf("Running child process PID: %d\n", getpid());

        // Call 'echoall' with 'execle', passing custom environment variables
        execle("/home/zachary4nier/bin/echoall", "echoall", "Bandicoot", "Pacman", (char *)NULL, custom_env);

        // If 'execle' fails, print the error message and exit
        perror("execle");
        exit(1);
    } else { // Parent process
        // Wait for the first child process to finish
        waitpid(first_child_pid, &status, 0);
    }

    // Fork the second child process
    second_child_pid = fork();

    if (second_child_pid == 0) { // Second child process
        printf("\nRunning child process PID: %d\n", getpid());

        // Call 'echoall' with 'execlp', using the filename
        execlp("echoall", "echoall", "Spyro", (char *)NULL);

        // If 'execlp' fails, print the error message and exit
        perror("execlp");
        exit(1);
    } else { // Parent process
        // Wait for the second child process to finish
        waitpid(second_child_pid, &status, 0);
    }

    // Exit the program
    exit(0);
}
