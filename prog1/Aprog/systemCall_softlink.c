#include<unistd.h>
#include<stdio.h>

int main(){
const char*target="/home/iiitb/ss/prog1/hello.c";
const char*linkpath="/home/iiitb/ss/prog1/Aprog/softlink";

int result = symlink(target, linkpath);

 if (result == 0) {
        printf("Symbolic link created successfully.\n");
 }
 else {
        perror("symlink");
    }

    return 0;
}
