#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 20
#define MAX_LINE 1024

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    char line[MAX_LINE];
    int line_count = 0;

    if (file == NULL) {
        perror(filename);
        return;
    }

    printf("\n===== Файл: %s =====\n\n", filename);

    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
        line_count++;

        if (line_count % LINES_PER_PAGE == 0) {
            printf("\n-- Натисніть Enter для продовження --");
            fflush(stdout);
            getchar();
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Використання: %s <файл1> [файл2 ...]\n", argv[0]);
        return 1;
    }

    printf("Задача 4: спрощена версія more\n");

    for (int i = 1; i < argc; i++) {
        print_file(argv[i]);
    }

    return 0;
}
