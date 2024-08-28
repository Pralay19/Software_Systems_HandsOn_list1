#include <unistd.h>
#include <stdlib.h>
#include<stdio.h>
int main() {
char arr[200];
read(0,arr,20);
write(1,arr,20);
printf("\n");
}
