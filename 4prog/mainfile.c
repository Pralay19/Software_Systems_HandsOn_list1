#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char buffer[256];

    // Open the file in read/write mode
    file = fopen("/home/iiitb/ss/4prog/example.txt", "r+");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    // Read the existing content
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("File content: %s\n", buffer);
    } else {
        printf("File is empty or error reading file.\n");
    }

    // Move the file pointer to the beginning
    fseek(file, 0, SEEK_SET);

    // Write new content
    fprintf(file, "Updated content\n");

    // Close the file
    fclose(file);

    return EXIT_SUCCESS;
}
