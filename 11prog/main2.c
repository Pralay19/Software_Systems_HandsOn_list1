#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
int fd, fd_dup;
const char *data1 = "Original FD write\n";
const char *data2 = "Duplicated FD write\n";


fd = open("second.txt", O_RDWR | O_APPEND);
if (fd == -1) {
perror("Error opening file");
return EXIT_FAILURE;
}


fd_dup = fcntl(fd, F_DUPFD, 0);
if (fd_dup == -1) {
perror("Error duplicating file descriptor");
close(fd);
return EXIT_FAILURE;
}


if (write(fd, data1, strlen(data1)) == -1) {
perror("Error writing with original FD");
close(fd);
close(fd_dup);
return EXIT_FAILURE;
}


if (write(fd_dup, data2, strlen(data2)) == -1) {
perror("Error writing with duplicated FD");
close(fd);
close(fd_dup);
return EXIT_FAILURE;
}


close(fd);
close(fd_dup);

printf("File 'second.txt' updated successfully with both file descriptors.\n");

return EXIT_SUCCESS;
}
