#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>

int main(){
random();
int r_num=rand()%100;
int fd=open("ticketData.txt",O_RDWR);
if (fd == -1) {
        perror("Error opening file");
        return 1;
    }
write(fd,&r_num,sizeof(r_num));
close(fd);
printf("Ticket Number generated:%d ",r_num);
}
