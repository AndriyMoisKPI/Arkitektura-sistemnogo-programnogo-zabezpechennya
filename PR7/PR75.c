#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <limits.h>

void list_files_recursive(const char *path, int level) {
    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        perror(path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[PATH_MAX];
        struct stat st;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &st) == -1) {
            perror(full_path);
            continue;
        }

        for (int i = 0; i < level; i++) {
            printf("  ");
        }

        if (S_ISDIR(st.st_mode)) {
            printf("[DIR]  %s\n", full_path);
            list_files_recursive(full_path, level + 1);
        } else {
            printf("[FILE] %s\n", full_path);
        }
    }

    closedir(dir);
}

int main(void) {
    printf("Задача 5: рекурсивний список файлів у поточному каталозі\n\n");

    list_files_recursive(".", 0);

    return 0;
}
