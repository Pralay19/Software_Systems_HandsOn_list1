#include<stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    struct flock lock; // Structure to define the file lock
    int fd = open("ticketData.txt", O_RDWR); // Open the file in read/write mode

    if (fd == -1) {
        perror("Error opening file"); // Error handling for file opening
        return 1;
    }

    // Initialize the flock structure
    memset(&lock, 0, sizeof(lock));
    lock.l_whence = SEEK_SET; // Starting point for the lock
    lock.l_start = 0;         // Offset from the l_whence
    lock.l_len = 0;           // 0 means lock the entire file
    
    int ticketNumber;
    
    // Set a read lock on the file
    lock.l_type = F_RDLCK;
    printf("Acquiring read lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire read lock");
        close(fd);
        return 1;
    }

    // Read the current ticket number from the file
    if (read(fd, &ticketNumber, sizeof(int)) !=sizeof(int)) {
        perror("Error reading ticket number");
        close(fd);
        return 1;
    }
    lseek(fd, 0, SEEK_SET); // Move file pointer back to re-read the same data

    printf("Current ticket number: %d\n", ticketNumber);

    // Set a write lock on the file
    lock.l_type = F_WRLCK;
    printf("Acquiring write lock...\n");
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to acquire write lock");
        close(fd);
        return 1;
    }

    // Increment the ticket number and write it back to the file
    ticketNumber++;
    if (write(fd, &ticketNumber, sizeof(int)) != sizeof(int)) {
        perror("Error writing updated ticket number");
        close(fd);
        return 1;
    }

    lseek(fd, 0, SEEK_SET); // Reposition file pointer to read the updated data

    if (read(fd, &ticketNumber, sizeof(int)) != sizeof(int)) {
        perror("Error reading updated ticket number");
        close(fd);
        return 1;
    }

    printf("Updated ticket number: %d\n", ticketNumber);

    // Wait for the user to press Enter before releasing the lock
    printf("Press Enter to release the lock and exit...");
    getchar();

    // Unlock the file
    lock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLKW, &lock) == -1) {
        perror("Failed to unlock file");
        close(fd);
        return 1;
    }

    // Close the file descriptor
    close(fd);
    return 0;
}
