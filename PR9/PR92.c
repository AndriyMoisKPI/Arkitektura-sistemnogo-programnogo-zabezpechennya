#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;

    printf("Завдання 9.2: читання /etc/shadow через sudo\n");
    printf("Програма запускає команду: sudo cat /etc/shadow\n\n");

    printf("Якщо система попросить пароль sudo, введіть пароль користувача.\n\n");

    result = system("sudo cat /etc/shadow");

    if (result == -1)
    {
        perror("Помилка виконання команди");
        return 1;
    }

    printf("\nКоманда завершила виконання.\n");

    if (result == 0)
    {
        printf("Висновок: файл /etc/shadow було прочитано через sudo.\n");
    }
    else
    {
        printf("Висновок: команду не вдалося виконати. Можливо, користувач не має прав sudo або пароль введено неправильно.\n");
    }

    return 0;
}
