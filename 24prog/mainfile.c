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
sleep(5);  // Sleep for a while to ensure the parent exits before the child
printf("Child process (PID: %d) is now an orphan, adopted by init/systemd. Parent PID: %d\n", getpid(), getppid());
} else {
// Parent process
printf("Parent process (PID: %d) is terminating.\n", getpid());
exit(0);  // Parent process exits, making the child an orphan
}

return 0;
}
