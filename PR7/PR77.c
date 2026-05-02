#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int has_c_extension(const char *filename) {
    size_t len = strlen(filename);

    if (len < 3) {
        return 0;
    }

    return strcmp(filename + len - 2, ".c") == 0;
}

int main(void) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Задача 7: надання іншим користувачам дозволу на читання для C-файлів\n\n");

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        char answer;

        if (!has_c_extension(entry->d_name)) {
            continue;
        }

        if (stat(entry->d_name, &st) == -1) {
            perror(entry->d_name);
            continue;
        }

        printf("Файл: %s\n", entry->d_name);
        printf("Поточні права: %o\n", st.st_mode & 0777);
        printf("Надати іншим користувачам дозвіл на читання? (y/n): ");

        scanf(" %c", &answer);

        if (answer == 'y' || answer == 'Y') {
            mode_t new_mode = st.st_mode | S_IROTH;

            if (chmod(entry->d_name, new_mode) == -1) {
                perror("chmod");
            } else {
                printf("Дозвіл на читання для інших додано.\n");
            }
        } else {
            printf("Файл залишено без змін.\n");
        }

        printf("\n");
    }

    closedir(dir);

    return 0;
}

