#include <time.h>    
#include <stdio.h>    
#include <stdlib.h>   
#include <sys/types.h> 
#include <unistd.h>    
#include <sys/stat.h>  

int main(int argc, char *argv[])
{
time_t now, target_time;
struct tm *target_tm;
pid_t pid;

if (argc < 2) {
fprintf(stderr, "Please provide at least one argument.\n");
return 1;
}

time(&now);
target_tm = localtime(&now);

target_tm->tm_hour = atoi(argv[1]);
target_tm->tm_min = (argc > 2) ? atoi(argv[2]) : 0;
target_tm->tm_sec = (argc > 3) ? atoi(argv[3]) : 0;

target_time = mktime(target_tm);

if ((pid = fork()) == 0) {
// Inside child process
if (setsid() < 0) {
    perror("setsid failed");
    exit(1);
}

if (chdir("/") < 0) {
    perror("chdir failed");
    exit(1);
}

umask(0);

while (difftime(target_time, time(NULL)) > 0) {
    sleep(1);  // Sleep for 1 second to avoid busy-waiting
}

printf("Surprise! Time has arrived!\n");
exit(0);
} else if (pid < 0) {
perror("fork failed");
return 1;
}

// Parent process exits
return 0;
}
