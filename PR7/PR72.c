#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

void print_permissions(mode_t mode) {
    printf((S_ISDIR(mode)) ? "d" : "-");
    printf((mode & S_IRUSR) ? "r" : "-");
    printf((mode & S_IWUSR) ? "w" : "-");
    printf((mode & S_IXUSR) ? "x" : "-");
    printf((mode & S_IRGRP) ? "r" : "-");
    printf((mode & S_IWGRP) ? "w" : "-");
    printf((mode & S_IXGRP) ? "x" : "-");
    printf((mode & S_IROTH) ? "r" : "-");
    printf((mode & S_IWOTH) ? "w" : "-");
    printf((mode & S_IXOTH) ? "x" : "-");
}

int main(void) {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(".");

    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Задача 2: спрощена реалізація ls -l\n\n");

    while ((entry = readdir(dir)) != NULL) {
        struct stat st;

        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &st) == -1) {
            perror(entry->d_name);
            continue;
        }

        print_permissions(st.st_mode);

        struct passwd *pw = getpwuid(st.st_uid);
        struct group *gr = getgrgid(st.st_gid);

        char timebuf[64];
        struct tm *tm_info = localtime(&st.st_mtime);

        if (tm_info != NULL) {
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", tm_info);
        } else {
            strcpy(timebuf, "unknown");
        }

        printf(" %2lu ", (unsigned long)st.st_nlink);
        printf("%-10s ", pw ? pw->pw_name : "unknown");
        printf("%-10s ", gr ? gr->gr_name : "unknown");
        printf("%8lld ", (long long)st.st_size);
        printf("%s ", timebuf);
        printf("%s\n", entry->d_name);
    }

    closedir(dir);

    return 0;
}
