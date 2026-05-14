#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LINE 1024

int main(void)
{
    FILE *fp;
    char line[MAX_LINE];

    uid_t current_uid = getuid();
    int found_other_users = 0;

    printf("Завдання 9.1: аналіз облікових записів через getent passwd\n");
    printf("UID поточного користувача: %d\n\n", current_uid);

    fp = popen("getent passwd", "r");
    if (fp == NULL)
    {
        perror("Помилка виконання getent passwd");
        return 1;
    }

    printf("Звичайні користувачі з UID >= 1000:\n");
    printf("----------------------------------------\n");

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *username;
        char *uid_str;
        int uid;

        username = strtok(line, ":");   // ім'я користувача
        strtok(NULL, ":");             // пароль або x
        uid_str = strtok(NULL, ":");   // UID

        if (username == NULL || uid_str == NULL)
        {
            continue;
        }

        uid = atoi(uid_str);

        if (uid >= 1000 && uid < 60000)
        {
            printf("Користувач: %-20s UID: %d", username, uid);

            if ((uid_t)uid == current_uid)
            {
                printf("  <-- поточний користувач");
            }
            else
            {
                printf("  <-- інший звичайний користувач");
                found_other_users = 1;
            }

            printf("\n");
        }
    }

    pclose(fp);

    printf("----------------------------------------\n");

    if (found_other_users)
    {
        printf("Висновок: у системі є інші звичайні користувачі, крім поточного.\n");
    }
    else
    {
        printf("Висновок: інших звичайних користувачів, крім поточного, не знайдено.\n");
    }

    return 0;
}
