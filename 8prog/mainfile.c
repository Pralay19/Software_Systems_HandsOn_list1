#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
int fd=open("file.txt",O_RDONLY);
while(1){
char c;
int i= read(fd,&c,1);
if(i==0){
	break;
}
if(i=='\n'){
	printf("\n");
}
else{
	printf("%c",c);
}
}


}
