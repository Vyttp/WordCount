#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024

// Function to count characters in the file
int count_characters(FILE *file) {
    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    return count;
}

// Function to count words in the file
int count_words(FILE *file) {
    int count = 0;
    char buffer[MAX_BUFFER_SIZE];
    char *token;
    
    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        token = strtok(buffer, " ,\t\n");
        while (token != NULL) {
            count++;
            token = strtok(NULL, " ,\t\n");
        }
    }
    
    return count;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s [-c | -w] input_file_name\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1];
    char *input_file_name = argv[2];
    FILE *file = fopen(input_file_name, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    if (strcmp(parameter, "-c") == 0) {
        int char_count = count_characters(file);
        printf("×Ö·ûÊý£º%d\n", char_count);
    } else if (strcmp(parameter, "-w") == 0) {
        rewind(file);  // Reset file pointer before reading again
        int word_count = count_words(file);
        printf("µ¥´ÊÊý£º%d\n", word_count);
    } else {
        fprintf(stderr, "Invalid parameter. Use -c to count characters or -w to count words.\n");
        fclose(file);
        return 1;
    }

    fclose(file);
    return 0;
}

