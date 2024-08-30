#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <string.h>

void print_policy(int policy) {
switch(policy) {
case SCHED_OTHER:
    printf("Current Scheduling Policy: SCHED_OTHER\n");
    break;
case SCHED_FIFO:
    printf("Current Scheduling Policy: SCHED_FIFO\n");
    break;
case SCHED_RR:
    printf("Current Scheduling Policy: SCHED_RR\n");
    break;
default:
    printf("Unknown Policy\n");
    break;
}
}

int main(int argc, char *argv[]) {
if (argc != 3) {
printf("Usage: %s <policy> <priority>\n", argv[0]);
printf("Policy can be 'fifo' or 'rr'.\n");
return 1;
}

int policy;
int priority = atoi(argv[2]);

if (strcmp(argv[1], "fifo") == 0) {
policy = SCHED_FIFO;
} else if (strcmp(argv[1], "rr") == 0) {
policy = SCHED_RR;
} else {
printf("Invalid policy. Use 'fifo' or 'rr'.\n");
return 1;
}

// Get the current scheduling policy
pid_t pid = getpid();
int current_policy = sched_getscheduler(pid);
if (current_policy == -1) {
perror("sched_getscheduler failed");
return 1;
}

print_policy(current_policy);

// Set the new scheduling policy
struct sched_param param;
param.sched_priority = priority;

if (sched_setscheduler(pid, policy, &param) == -1) {
perror("sched_setscheduler failed");
return 1;
}

printf("Scheduling policy changed successfully.\n");

// Verify the new scheduling policy
current_policy = sched_getscheduler(pid);
if (current_policy == -1) {
perror("sched_getscheduler failed");
return 1;
}

print_policy(current_policy);

return 0;
}
