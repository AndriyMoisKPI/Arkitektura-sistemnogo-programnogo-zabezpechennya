#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;

    printf("Завдання 9.4: перевірка користувача через whoami та id\n\n");

    printf("1. Виконання команди whoami:\n");
    result = system("whoami");

    if (result != 0)
    {
        printf("Помилка виконання команди whoami\n");
        return 1;
    }

    printf("\n2. Виконання команди id:\n");
    result = system("id");

    if (result != 0)
    {
        printf("Помилка виконання команди id\n");
        return 1;
    }

    printf("\nКоротке пояснення:\n");
    printf("Команда whoami показує ім'я поточного користувача.\n");
    printf("Команда id показує UID, GID та групи, до яких належить користувач.\n");

    printf("\nВисновок: програма показала стан облікового запису користувача, ");
    printf("від імені якого вона була запущена.\n");

    return 0;
}
