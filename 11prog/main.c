#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
int fd, fd_dup;
const char *text1 = "Writing with original descriptor.\n";
const char *text2 = "Writing with duplicated descriptor.\n";


fd = open("first.txt", O_WRONLY | O_APPEND | O_CREAT, 0666);
if (fd == -1) {
perror("Error opening file");
return EXIT_FAILURE;
}


fd_dup = dup(fd);
if (fd_dup == -1) {
perror("Error duplicating file descriptor");
close(fd);
return EXIT_FAILURE;
}

if (write(fd, text1, sizeof(text1)) == -1) {
perror("Error writing with original descriptor");
close(fd);
close(fd_dup);
return EXIT_FAILURE;
}


if (write(fd_dup, text2, sizeof(text2)) == -1) {
perror("Error writing with duplicated descriptor");
close(fd);
close(fd_dup);
return EXIT_FAILURE;
}

close(fd);
close(fd_dup);

printf("File updated successfully.\n");

return EXIT_SUCCESS;
}

