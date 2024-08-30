#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

int main() {

// Open a file for writing (creates it if it doesn't exist, truncates it if it does)
int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
if (fd == -1) {
perror("Error opening file");
return 1;
}

// Buffer to write
 char *parent_msg = "This is the parent process writing.\n";
 char *child_msg = "This is the child process writing.\n";

// Call fork to create a new process
pid_t pid = fork();

if (pid == -1) {
// If fork failed
perror("fork failed");
close(fd);
return 1;
}

if (pid == 0) {
// Child process
pid_t pid1=getpid();
printf("Child process pid %d...\n",pid1);
char*cpid;
sprintf(cpid,"%d",pid1);
strcat(child_msg,cpid);
write(fd, child_msg, strlen(child_msg));
} else {
// Parent process
pid_t pid2=getpid();
printf("Parent process pid %d...\n",pid2);
char*ppid;
sprintf(ppid,"%d",pid2);
strcat(parent_msg,ppid);
write(fd, parent_msg, strlen(parent_msg));

// Wait for the child process to complete
wait(NULL);
}

// Close the file
close(fd);
return 0;
}
