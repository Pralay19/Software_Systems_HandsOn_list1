#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

printf("Trying execl:\n");
if (fork() == 0) {
execl("/usr/bin/ls", "ls", "-Rl", NULL);
perror("execl");
exit(1);
}
printf("\n");
printf("Trying execlp:\n");
if (fork() == 0) {
execlp("ls", "ls", "-Rl", NULL);
perror("execlp");
exit(1);
}
printf("\n");
printf("Trying execle:\n");
char *envp[] = { NULL };
if (fork() == 0) {
char *args[] = { "ls", "-Rl", NULL };
execle("/usr/bin/ls", "ls", "-Rl", NULL, envp);
perror("execle");
exit(1);
}
printf("\n");
printf("Trying execv:\n");
if (fork() == 0) {
char *args[] = { "/usr/bin/ls", "ls", "-Rl", NULL };
execv("/usr/bin/ls", args);
perror("execv");
exit(1);
}
printf("\n");
printf("Trying execvp:\n");
if (fork() == 0) {
char *args[] = { "ls", "ls", "-Rl", NULL };
execvp("ls", args);
perror("execvp");
exit(1);
}

return 0;
}
