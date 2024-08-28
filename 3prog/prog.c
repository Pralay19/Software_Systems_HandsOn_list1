#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;

    // Create a new file named "my_file.txt" with read and write permissions
    fd = creat("my_file.txt", 0666);

    if (fd == -1) {
        perror("creat");
        return 1;
    }

    printf("File descriptor value: %d\n", fd);

    // Close the file
    close(fd);

    return 0;
}
