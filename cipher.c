#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int choice;
    char path[PATH_MAX];

    while (1) {
        if (scanf("%d", &choice) != 1) {
            printf("n/a\n");
            return 0;
        }

        if (choice == -1) {
            return 0;
        } else if (choice == 1) {
            scanf("%s", path);

            FILE *file = fopen(path, "r");
            if (file == NULL) {
                printf("n/a\n\n");
                continue;
            }

            int ch;
            int isEmpty = 1;

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