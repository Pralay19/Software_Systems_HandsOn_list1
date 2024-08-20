#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

const char*fifo_path= "/home/iiitb/ss/prog1/Cprog/sys_FIFO";
int fd;
char buffer[128];

fd=open(fifo_path,O_RDONLY);
if(fd==-1){
	perror("open");
	exit(EXIT_FAILURE);
}
ssize_t data= read(fd,buffer,sizeof(buffer)-1);
if(data>0){
	buffer[data]='\0';
	printf("Message from the FIFO: %s \n",buffer);
}
else{
perror("read");
}
close(fd);

return 0;
}
