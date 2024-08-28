#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int fd;
    const char *filename = "/home/iiitb/ss/4prog/example2.txt";

    // Open file with O_CREAT and O_EXCL flags
    fd = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);

    if (fd == -1) {
        if (errno == EEXIST) {
            printf("Error: File '%s' already exists.\n", filename);
        } else {
            perror("Error opening file");
        }
        return EXIT_FAILURE;
    }

    // Write some content to the file
    write(fd, "New file content\n", 17);

    // Close the file
    close(fd);

    printf("File '%s' created and written successfully.\n", filename);

    return EXIT_SUCCESS;
}
