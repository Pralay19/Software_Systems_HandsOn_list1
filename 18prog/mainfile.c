#include <stdio.h>    
#include <fcntl.h>    
#include <unistd.h>   


struct student {
int roll_no=-1;
int marks=-1;
};

void createRecord(int roll_no, int marks) {
int fd = open("./test_dir_02/test_file_07.txt", O_RDWR | O_CREAT, 0666);
if(fd == -1) {
perror("Error opening file");
return 1;
}
}

int main()
{

return 0;
}
