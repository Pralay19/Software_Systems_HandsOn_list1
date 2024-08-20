#include<stdio.h>
#include<sys/stat.h>

int main(){

if(mkfifo("systemCall_myFIFO",0666)==-1){
	perror("mkfifo");
	return 1;
}
printf("FIFO created successfully.");
return 0;
}
