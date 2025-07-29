#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_INPUT 1024

char current_path[PATH_MAX] = "";

void print_file(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        printf("n/a\n");
        return;
    }
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }
    fclose(file);
    printf("\n");
}

void append_to_file(const char *path) {
    FILE *file = fopen(path, "a");
    if (!file) {
        printf("n/a\n");
        return;
    }

    char buffer[MAX_INPUT];
    getchar();
    if (!fgets(buffer, MAX_INPUT, stdin)) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    size_t len = strlen(buffer);

    fprintf(file, "\n%s", buffer);
    fclose(file);

    print_file(path);
}

void caesar_encrypt_file(const char *path, int shift) {
    FILE *file = fopen(path, "r");
    if (!file) return;

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *content = malloc(size + 1);
    if (!content) {
        fclose(file);
        return;
    }
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);

    for (long i = 0; i < size; ++i) {
        if ((content[i] >= 'A' && content[i] <= 'Z') || (content[i] >= 'a' && content[i] <= 'z')) {
            char base = (content[i] >= 'a') ? 'a' : 'A';
            content[i] = (content[i] - base + shift) % 26 + base;
        }
    }

    file = fopen(path, "w");
    if (!file) {
        free(content);
        return;
    }
    fwrite(content, 1, size, file);
    fclose(file);
    free(content);
}

void process_directory(const char *dir_path, int shift) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        printf("n/a\n");
        return;
    }

    struct dirent *entry;
    struct stat st;
    char full_path[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

        if (stat(full_path, &st) == -1)
            continue;

        if (S_ISREG(st.st_mode)) {
            if (strstr(entry->d_name, ".c")) {
                caesar_encrypt_file(full_path, shift);
            } else if (strstr(entry->d_name, ".h")) {
                FILE *file = fopen(full_path, "w");
                if (file) fclose(file);
            }
        }
    }
    closedir(dir);
}

int main() {
    int choice;

    while (1) {
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            break;
        }

        if (choice == -1) {
            break;
        } else if (choice == 1) {
            if (scanf("%259s", current_path) != 1) {
                printf("n/a\n");
            } else {
                print_file(current_path);
            }
        } else if (choice == 2) {
            if (strlen(current_path) == 0) {
                printf("n/a\n");
            } else {
                append_to_file(current_path);
            }
        } else if (choice == 3) {
            int shift;
            if (scanf("%d", &shift) != 1) {
                printf("n/a\n");
            } else {
                process_directory("src", shift);
            }
        } else {
            printf("n/a\n");
        }
    }

    return 0;
}
