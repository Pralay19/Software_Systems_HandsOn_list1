#include <stdio.h>
#include<sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
int fd = open("first.txt", O_RDWR|O_CREAT,0666);
if (fd == -1) {
perror("Error opening file");
return 1;
}
char data1[] = "HAPPYlappy";
int w = write(fd, data1, sizeof(data1));
if (w == -1) {
perror("Error writing data");
return 1;
}
int offset = 10;
int l = lseek(fd, -1*offset, SEEK_CUR);
printf("This is what lseek returns: %d\n", l);
char data2[] = "1234567890";
w = write(fd, data2, sizeof(data2));
if (w == -1) {
perror("Error writing data");
close(fd);
return 1;
}
close(fd);
return 0;
}
