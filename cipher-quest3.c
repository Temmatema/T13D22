#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <ctype.h>

int caesar_encrypt_file(const char *filename, int shift) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    rewind(file);

    char *buffer = malloc(len + 1);
    if (!buffer) {
        fclose(file);
        return 0;
    }

    fread(buffer, 1, len, file);
    buffer[len] = '\0';
    fclose(file);

    for (long i = 0; i < len; ++i) {
        if (isprint(buffer[i])) {
            buffer[i] = (char)(((buffer[i] - 32 + shift) % 95) + 32);
        }
    }

    file = fopen(filename, "w");
    if (!file) {
        free(buffer);
        return 0;
    }

    fwrite(buffer, 1, len, file);
    fclose(file);
    free(buffer);
    return 1;
}

int clear_header_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;
    fclose(file);
    return 1;
}

void process_directory(const char *dir_path, int shift) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        printf("n/a\n\n");
        return;
    }

    struct dirent *entry;
    char fullpath[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_REG) continue;

        const char *name = entry->d_name;
        size_t len = strlen(name);

        snprintf(fullpath, PATH_MAX, "%s/%s", dir_path, name);

        if (len > 2 && strcmp(name + len - 2, ".c") == 0) {
            if (!caesar_encrypt_file(fullpath, shift)) {
                printf("n/a\n\n");
                closedir(dir);
                return;
            }
        } else if (len > 2 && strcmp(name + len - 2, ".h") == 0) {
            if (!clear_header_file(fullpath)) {
                printf("n/a\n\n");
                closedir(dir);
                return;
            }
        }
    }

    closedir(dir);
}

int main() {
    int choice;
    char path[PATH_MAX] = "";
    int file_loaded = 0;

    while (1) {
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            return 0;
        }

        getchar();

        if (choice == -1) {
            return 0;
        } else if (choice == 1) {
            if (scanf("%s", path) != 1) {
                printf("n/a\n\n");
                continue;
            }

            FILE *file = fopen(path, "r");
            if (file == NULL) {
                printf("n/a\n\n");
                continue;
            }

            int ch, isEmpty = 1;
            while ((ch = fgetc(file)) != EOF) {
                putchar(ch);
                isEmpty = 0;
            }
            fclose(file);

            if (isEmpty) {
                printf("n/a");
            } else {
                file_loaded = 1;
            }

            printf("\n\n");

        } else if (choice == 2) {
            if (!file_loaded) {
                printf("n/a\n\n");
                continue;
            }

            char buffer[1024];
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("n/a\n\n");
                continue;
            }

            buffer[strcspn(buffer, "\n")] = '\0';

            FILE *file = fopen(path, "a");
            if (!file) {
                printf("n/a\n\n");
                continue;
            }

            fprintf(file, "%s\n", buffer);
            fclose(file);

            file = fopen(path, "r");
            if (!file) {
                printf("n/a\n\n");
                continue;
            }

            int ch, isEmpty = 1;
            while ((ch = fgetc(file)) != EOF) {
                putchar(ch);
                isEmpty = 0;
            }
            fclose(file);

            if (isEmpty) {
                printf("n/a");
            }

            printf("\n\n");

        } else if (choice == 3) {
            char dir[PATH_MAX];
            int shift;

            if (scanf("%s", dir) != 1) {
                printf("n/a\n\n");
                continue;
            }

            if (scanf("%d", &shift) != 1) {
                printf("n/a\n\n");
                continue;
            }

            getchar();
            process_directory(dir, shift);

        } else {
            printf("n/a\n\n");
        }
    }

    return 0;
}
