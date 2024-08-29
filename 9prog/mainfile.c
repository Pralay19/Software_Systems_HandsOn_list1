#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

void print_file_info(const char *filename) {
struct stat file_info;

if (stat(filename, &file_info) == -1) {
perror("Error");
exit(EXIT_FAILURE);
}

printf("inode: %ld\n", file_info.st_ino);
printf("Number of hard links: %ld\n", file_info.st_nlink);
 
struct passwd *pw = getpwuid(file_info.st_uid);
if (pw != NULL) {
printf("uid: %s\n", pw->pw_name);
} else {
printf("uid: %d\n", file_info.st_uid);
}

struct group *gr = getgrgid(file_info.st_gid);
if (gr != NULL) {
printf("gid: %s\n", gr->gr_name);
} else {
printf("gid: %d\n", file_info.st_gid);
}

printf("Size: %ld bytes\n", file_info.st_size);
printf("Block size: %ld\n", file_info.st_blksize);
printf("Number of blocks: %ld\n", file_info.st_blocks);

printf("Time of last access: %s", ctime(&file_info.st_atime));
printf("Time of last modification: %s", ctime(&file_info.st_mtime));
printf("Time of last change: %s", ctime(&file_info.st_ctime));
}

int main(int argc, char *argv[]) {
if (argc != 2) {
fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
return EXIT_FAILURE;
}

print_file_info(argv[1]);

return 0;
}
