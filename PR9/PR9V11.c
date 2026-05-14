#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <grp.h>

#define MAX_GROUPS 64
#define MAX_LINE 256

int main(void)
{
    int result;
    gid_t groups[MAX_GROUPS];
    int group_count;
    FILE *fp;
    char line[MAX_LINE];

    printf("Варіант 11: порівняння виконання id у shell та через системні виклики\n\n");

    printf("1. Виконання команди id через system():\n");
    result = system("id");

    if (result != 0)
    {
        printf("Помилка виконання команди id через system().\n");
    }

    printf("\n2. Отримання інформації через системні виклики:\n");

    printf("getuid()  = %d\n", getuid());
    printf("geteuid() = %d\n", geteuid());
    printf("getgid()  = %d\n", getgid());
    printf("getegid() = %d\n", getegid());

    group_count = getgroups(MAX_GROUPS, groups);

    if (group_count == -1)
    {
        perror("Помилка getgroups");
        return 1;
    }

    printf("Групи користувача через getgroups(): ");

    for (int i = 0; i < group_count; i++)
    {
        printf("%d", groups[i]);

        if (i < group_count - 1)
        {
            printf(", ");
        }
    }

    printf("\n");

    printf("\n3. Виконання id через popen() і читання результату:\n");

    fp = popen("id", "r");

    if (fp == NULL)
    {
        perror("Помилка popen");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%s", line);
    }

    pclose(fp);

    printf("\n4. Додаткова перевірка середовища:\n");
    printf("Поточна оболонка користувача:\n");
    system("echo $SHELL");

    printf("\nПоточний робочий каталог:\n");
    system("pwd");

    printf("\nВисновок:\n");
    printf("Команда id у shell та через system()/popen() запускається як окремий процес.\n");
    printf("Системні виклики getuid(), getgid() і getgroups() отримують інформацію напряму з ядра Linux.\n");
    printf("У звичайному запуску результати збігаються, але спосіб отримання інформації різний.\n");

    return 0;
}
