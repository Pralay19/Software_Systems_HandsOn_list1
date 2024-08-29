#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
fd_set readfds;
FD_ZERO(&readfds);
FD_SET(STDIN_FILENO, &readfds);
struct timeval timeout;
timeout.tv_sec = 10;
timeout.tv_usec = 0;
printf("Waiting for  stdin  10 seconds...\n");
int r = select(STDIN_FILENO+1, &readfds, NULL, NULL, &timeout);
if (r == -1) {
perror("Error in select");
return 1;
} 
else if (r == 0) {
printf("No input received within 10 seconds.\n");
} 
else {
printf("Input is available on stdin.\n");
fflush(stdin);
}
close(STDIN_FILENO);
return 0;
}
