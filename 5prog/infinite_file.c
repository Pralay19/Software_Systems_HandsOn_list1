#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>

int main(){
printf("PID : %d\n",getpid());
while(1){
int fd = open("file1",O_CREAT);
if(fd==-1){
	printf("ERROR\n");
	sleep(150);
	break;
}
int fd1 = open("file2",O_CREAT);
if(fd1==-1){
	printf("ERROR\n");
	sleep(150);
	break;
}
int fd2 = open("file3",O_CREAT);
if(fd1==-1){
        printf("ERROR\n");
        sleep(150);
        break;
}
int fd3 = open("file4",O_CREAT);
if(fd1==-1){
        printf("ERROR\n");
        sleep(150);
        break;
}
int fd4 = open("file5",O_CREAT);
if(fd1==-1){
        printf("ERROR\n");
        sleep(150);
        break;
}
printf("%d %d %d %d %d",fd,fd1,fd2,fd3,fd4);
}


}
