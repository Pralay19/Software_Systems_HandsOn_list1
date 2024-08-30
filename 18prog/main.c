#include <stdio.h>    
#include <fcntl.h>    
#include <unistd.h>   
#include <stdlib.h>   
#include <time.h>     

struct Record {
int id;
int score;
};

int acquire_read_lock(int record_num);
int acquire_write_lock(int record_num);

int acquire_read_lock(int record_num) {
int file_desc = open("record_file.txt", O_RDONLY);
if (file_desc == -1) {
perror("Failed to open file");
return 1;
}

struct Record rec;

lseek(file_desc, (record_num - 1) * sizeof(struct Record), SEEK_SET);
read(file_desc, &rec, sizeof(struct Record));
printf("ID: %d \t Score: %d \n", rec.id, rec.score);

struct flock lock;
lock.l_type = F_RDLCK;
lock.l_whence = SEEK_SET;
lock.l_start = (record_num - 1) * sizeof(struct Record);
lock.l_len = sizeof(struct Record);

printf("Attempting to acquire read lock on record %d \n", rec.id);
fcntl(file_desc, F_SETLKW, &lock);

printf("Read lock acquired on record %d \n", rec.id);
printf("Press Enter to release the lock\n");

getchar();
getchar();

lock.l_type = F_UNLCK;
fcntl(file_desc, F_SETLKW, &lock);
printf("Released read lock\n");

close(file_desc);
return 0;
}

int acquire_write_lock(int record_num) {
int file_desc = open("record_file.txt", O_RDWR);
if (file_desc == -1) {
perror("Failed to open file");
return 1;
}

struct Record rec;

lseek(file_desc, (record_num - 1) * sizeof(struct Record), SEEK_SET);
read(file_desc, &rec, sizeof(struct Record));
printf("ID: %d \n", rec.id);
printf("Current Score: %d\n", rec.score);

struct flock lock;
lock.l_type = F_WRLCK;
lock.l_whence = SEEK_SET;
lock.l_start = (record_num - 1) * sizeof(struct Record);
lock.l_len = sizeof(struct Record);

printf("Attempting to acquire write lock on record %d \n", rec.id);
if (fcntl(file_desc, F_SETLKW, &lock) < 0) {
perror("Locking error");
return 1;
}

printf("Write lock acquired on record %d \n", rec.id);
printf("Enter new score: ");
scanf("%d", &rec.score);

lseek(file_desc, -1 * sizeof(struct Record), SEEK_CUR);
write(file_desc, &rec, sizeof(struct Record));

printf("Updated ID: %d \n", rec.id);
printf("Updated Score: %d\n", rec.score);

printf("Press Enter to release the lock\n");
getchar();
getchar();

lock.l_type = F_UNLCK;
fcntl(file_desc, F_SETLKW, &lock);
printf("Released write lock\n");

close(file_desc);
return 0;
}

int main() {
int file_desc = open("record_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);
if (file_desc == -1) {
perror("Error creating file");
return 1;
}

int num_records = 3;
printf("Enter the number of records to create: ");
scanf("%d", &num_records);
srand(time(NULL));

struct Record rec;
for (int i = 0; i < num_records; i++) {
rec.id = 1000 + i;
rec.score = rand() % 100;
write(file_desc, &rec, sizeof(struct Record));
}

lseek(file_desc, 0, SEEK_SET);
printf("Records:\n");
for (int i = 0; i < num_records; i++) {
read(file_desc, &rec, sizeof(struct Record));
printf("ID: %d\tScore: %d\n", rec.id, rec.score);
}

lseek(file_desc, 0, SEEK_SET);

int record_num, option;
printf("Enter the record number to lock: ");
scanf("%d", &record_num);
if (record_num <= 0 || record_num > num_records) {
printf("Invalid record number\n");
return 1;
}

printf("Select lock type: Read (1) Write (2): ");
scanf("%d", &option);
if (option == 1) {
acquire_read_lock(record_num);
} else if (option == 2) {
acquire_write_lock(record_num);
} else {
printf("Invalid choice\n");
}

close(file_desc);

return 0;
}
