#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>

int main(int argc, char * argv[]){
int fd = open("first.txt", O_RDWR);
if(fd==-1){
perror("Cant open the file");
return 1;
}
int flags = fcntl(fd,F_GETFL);
if(flags==-1){
perror("Error");
return 1;
}
if(flags==32768){
printf("The file is opened in O_RDONLY mode.\n");
}
else if(flags==32769){
printf("The file is opened in O_WRONLY mode.\n");
}
else{
printf("The file is opened in O_RDWR mode.\n");
}
return 0;
}
