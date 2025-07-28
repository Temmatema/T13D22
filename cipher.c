#include <stdio.h>
#include <limits.h>
#include <string.h>

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
            if (file == NULL) {
                printf("n/a\n\n");
                continue;
            }

            fprintf(file, "%s\n", buffer);
            fclose(file);

            file = fopen(path, "r");
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
            }

            printf("\n\n");

        } else {
            printf("n/a\n\n");
        }
    }

    return 0;
}
