#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2, pid3;
    int status;

    // Create the first child process
    pid1 = fork();
    if (pid1 == -1) {
        perror("Failed to fork");
        exit(1);
    } else if (pid1 == 0) {
        // In the first child process
        printf("First child process (PID: %d)\n", getpid());
        sleep(2); // Simulate some work
        exit(0);
    }

    // Create the second child process
    pid2 = fork();
    if (pid2 == -1) {
        perror("Failed to fork");
        exit(1);
    } else if (pid2 == 0) {
        // In the second child process
        printf("Second child process (PID: %d)\n", getpid());
        sleep(4); // Simulate some work
        exit(0);
    }

    // Create the third child process
    pid3 = fork();
    if (pid3 == -1) {
        perror("Failed to fork");
        exit(1);
    } else if (pid3 == 0) {
        // In the third child process
        printf("Third child process (PID: %d)\n", getpid());
        sleep(6); // Simulate some work
        exit(0);
    }

    // Parent process waits for the second child to finish
    printf("Parent process waiting for the second child (PID: %d)\n", pid2);
    if (waitpid(pid2, &status, 0) == -1) {
        perror("Failed to wait for child");
        exit(1);
    }

    if (WIFEXITED(status)) {
        printf("Second child exited with status: %d\n", WEXITSTATUS(status));
    } else {
        printf("Second child did not exit normally\n");
    }

    // Optionally, the parent can wait for the remaining children
    waitpid(pid1, &status, 0);
    waitpid(pid3, &status, 0);

    printf("Parent process finished\n");

    return 0;
}
