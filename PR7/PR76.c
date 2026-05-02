#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>

#define MAX_DIRS 1024

int compare_strings(const void *a, const void *b) {
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;
    return strcmp(str1, str2);
}

int main(void) {
    DIR *dir;
    struct dirent *entry;
    char *directories[MAX_DIRS];
    int count = 0;

    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Задача 6: список лише підкаталогів в алфавітному порядку\n\n");

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;
        char path[PATH_MAX];

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "./%s", entry->d_name);

        if (stat(path, &st) == -1) {
            perror(path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            if (count < MAX_DIRS) {
                directories[count] = malloc(strlen(entry->d_name) + 1);

                if (directories[count] == NULL) {
                    perror("malloc");
                    closedir(dir);
                    return 1;
                }

                strcpy(directories[count], entry->d_name);
                count++;
            }
        }
    }

    closedir(dir);

    qsort(directories, count, sizeof(char *), compare_strings);

    printf("Підкаталоги:\n");

    for (int i = 0; i < count; i++) {
        printf("%s\n", directories[i]);
        free(directories[i]);
    }

    if (count == 0) {
        printf("Підкаталогів не знайдено.\n");
    }

    return 0;
}

