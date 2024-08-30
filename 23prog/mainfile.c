#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
pid_t pid = fork();

if (pid < 0) {
// Fork failed
perror("Fork failed");
return 1;
}

if (pid == 0) {
// Child process
printf("Child process (PID: %d) is terminating.\n", getpid());
exit(0); // Child exits, becoming a zombie until the parent reaps it
} else {
// Parent process
printf("Parent process (PID: %d) created a child process (PID: %d).\n", getpid(), pid);

// Sleep to give the child time to exit and become a zombie
sleep(10);

// Now, let's wait for the child process to terminate
printf("Parent is now waiting for child to terminate...\n");
wait(NULL); // Reap the child process

printf("Child process reaped by parent.\n");
}

return 0;
}
