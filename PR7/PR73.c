#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    FILE *file;
    char line[MAX_LINE];
    int line_number = 0;
    int found = 0;

    if (argc != 3) {
        printf("Використання: %s <слово> <файл>\n", argv[0]);
        return 1;
    }

    file = fopen(argv[2], "r");

    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    printf("Задача 3: проста версія grep\n\n");
    printf("Пошук слова \"%s\" у файлі %s\n\n", argv[1], argv[2]);

    while (fgets(line, sizeof(line), file) != NULL) {
        line_number++;

        if (strstr(line, argv[1]) != NULL) {
            printf("%d: %s", line_number, line);
            found = 1;
        }
    }

    fclose(file);

    if (!found) {
        printf("Рядків зі словом \"%s\" не знайдено.\n", argv[1]);
    }

    return 0;
}
