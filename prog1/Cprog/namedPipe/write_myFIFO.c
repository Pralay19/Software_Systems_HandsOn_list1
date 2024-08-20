#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
const char *fifo_path="/home/iiitb/ss/prog1/Cprog/sysFIFO";
int fd;
fd=open(fifo_path,O_WRONLY);
if(fd==-1){
	perror("open");
	exit(EXIT_FAILURE);
}

const char *message="Hello I am inside a FIFO made using system calls and this was written using another C program.\n";
write(fd,message,sizeof(message));

printf("Message was written into the FIFO.\n");
close(fd);
return 0;
}
