#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/file.h>
// Define the structure for train information
struct Train {
char train_no[10];
char train_name[100];
int tickets;
};



void initialize_train_data() {
FILE *file = fopen("train_data", "wb");
if (file == NULL) {
perror("Error opening file");
exit(EXIT_FAILURE);
}

while (1) {
struct Train train;

printf("Enter train number (type 'done' to finish) : ");
scanf("%s", train.train_no);
if (strcmp(train.train_no, "done") == 0) {
    break;
}

printf("Enter name for train %s: ", train.train_no);
scanf("%s", train.train_name);
train.tickets=0;

fwrite(&train, sizeof(struct Train), 1, file);
}

fclose(file);
printf("\nTrain data has been initialized and saved.\n");
}

void load_train_data() {
FILE *file = fopen("train_data", "rb");
if (file == NULL) {
perror("Error opening file");
exit(EXIT_FAILURE);
}

struct Train train;
printf("Train Data:\n");
while (fread(&train, sizeof(struct Train), 1, file)) {
printf("Train No: %s, Name: %s , Total Tickets: %d\n",
       train.train_no, train.train_name,train.tickets);
}

fclose(file);
}

void book_train() {
int fd = open("train_data", O_RDWR);
if (fd == -1) {
perror("Error opening file");
exit(EXIT_FAILURE);
}

// Lock the file
if (flock(fd, LOCK_EX) == -1) {
perror("Error locking file");
close(fd);
exit(EXIT_FAILURE);
}

struct Train train;
int found = 0;

printf("Enter the train number you want to book: ");
char train_no[10];
scanf("%s", train_no);

FILE *file = fdopen(fd, "r+b");
while (fread(&train, sizeof(struct Train), 1, file)) {
if (strcmp(train.train_no, train_no) == 0) {
    printf("Booking confirmed for Train: %s\n",
           train.train_name);
    train.tickets+=1;
    fseek(file, -sizeof(struct Train), SEEK_CUR);

    // Update the record with the new number of tickets booked
    fwrite(&train, sizeof(struct Train), 1, file);
    fflush(file);  // Ensure data is written to disk
    found = 1;
    break;
}
}

if (!found) {
printf("Train number %s does not exist.\n", train_no);
}

// Unlock the file
if (flock(fd, LOCK_UN) == -1) {
perror("Error unlocking file");
close(fd);
exit(EXIT_FAILURE);
}

fclose(file);
close(fd);
}

int main() {
int choice;

// Check if train data exists, if not, initialize it
if (access("train_data", F_OK) == -1) {
printf("No train data found. Let's initialize the data.\n");
initialize_train_data();
}

while (1) {
printf("\nOptions:\n");
printf("1. Book a train\n");
printf("2. View train data\n");
printf("3. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);

switch (choice) {
    case 1:
        book_train();
        break;
    case 2:
        load_train_data();
        break;
    case 3:
        printf("Exiting the program.\n");
        exit(0);
    default:
        printf("Invalid choice. Please try again.\n");
}
}

return 0;
}
