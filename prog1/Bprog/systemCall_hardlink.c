#include<unistd.h>
#include<stdio.h>

int main(){

const char*target="/home/iiitb/ss/prog1/hello.c";
const char*linkpath="/home/iiitb/ss/prog1/Bprog/hardlink_createdUsingSystemCall";

int result=link(target,linkpath);
if(result==0)
	printf("Hardlink created successfully.\n");
else
	perror("link");
return 0;
}
