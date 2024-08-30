#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
int main(){
printf("enter your input:\n");
char str[100];
scanf("%s",str);
char file[10] ="./test ";
strcat(file,str);
int status  = system(file);
return 0;
}
