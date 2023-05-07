#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILES 100
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int size;
} file_t;

file_t files[MAX_FILES];
int num_files = 0;

void add_file(char* name, int size) {
    if (num_files == MAX_FILES) {
        printf("Maximum number of files reached.\n");
        return;
    }

    if (strlen(name) > MAX_NAME_LENGTH - 1) {
        printf("File name is too long.\n");
        return;
    }

    strcpy(files[num_files].name, name);
    files[num_files].size = size;
    num_files++;

    printf("File added: %s\n", name);
}

void list_files() {
    printf("Listing files:\n");
    for (int i = 0; i < num_files; i++) {
        printf("%s (%d bytes)\n", files[i].name, files[i].size);
    }
}

void delete_file(char* name) {
    int index = -1;
    for (int i = 0; i < num_files; i++) {
        if (strcmp(files[i].name, name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("File not found.\n");
        return;
    }

    for (int i = index; i < num_files - 1; i++) {
        files[i] = files[i + 1];
    }

    num_files--;

    printf("File deleted: %s\n", name);
}

int main() {
    add_file("file1.txt", 100);
    add_file("file2.txt", 200);
    list_files();
    delete_file("file1.txt");
    list_files();
    add_file("file3.txt", 150);
    list_files();

    return 0;
}

