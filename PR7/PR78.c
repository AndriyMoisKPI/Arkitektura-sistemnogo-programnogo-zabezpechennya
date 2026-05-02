#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    DIR *dir;
    struct dirent *entry;
    char answer;

    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Задача 8: інтерактивне видалення файлів у поточному каталозі\n\n");

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &st) == -1) {
            perror(entry->d_name);
            continue;
        }

        if (!S_ISREG(st.st_mode)) {
            continue;
        }

        printf("Файл: %s\n", entry->d_name);
        printf("Видалити цей файл? (y/n): ");
        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            if (remove(entry->d_name) == 0) {
                printf("Файл видалено.\n");
            } else {
                perror("remove");
            }
        } else {
            printf("Файл залишено.\n");
        }

        printf("\n");
    }

    closedir(dir);

    return 0;
}
