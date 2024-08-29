#include <stdio.h>
#include <unistd.h>
#include <time.h>

int main() {
    struct timespec start, end;

    // Record the start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Execute the getpid() system call
    pid_t pid = getpid();

    // Record the end time
    clock_gettime(CLOCK_MONOTONIC, &end);

    // Calculate the time taken (in nanoseconds)
    long seconds = end.tv_sec - start.tv_sec;
    long nanoseconds = end.tv_nsec - start.tv_nsec;
    long elapsed = seconds * 1e9 + nanoseconds;

    // Print the result
    printf("getpid() system call was executed in %ld nanoseconds\n", elapsed);
    printf("Process ID: %d\n", pid);

    return 0;
}
