#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;

    printf("Завдання 9.3: файл створюється користувачем, а копія робиться від root\n\n");

    printf("1. Створення початкового файлу від імені звичайного користувача...\n");
    result = system("echo 'Початковий текст у файлі користувача' > user_file.txt");

    if (result != 0)
    {
        printf("Помилка створення user_file.txt\n");
        return 1;
    }

    printf("Файл user_file.txt створено.\n\n");

    printf("2. Копіювання файлу через sudo у домашній каталог...\n");
    result = system("sudo cp user_file.txt root_copy.txt");

    if (result != 0)
    {
        printf("Помилка копіювання файлу через sudo.\n");
        return 1;
    }

    printf("Копію root_copy.txt створено.\n\n");

    printf("3. Перегляд власника і прав доступу:\n");
    system("ls -l user_file.txt root_copy.txt");

    printf("\n4. Спроба змінити root_copy.txt від імені звичайного користувача...\n");
    result = system("echo 'Спроба дописати текст звичайним користувачем' >> root_copy.txt");

    if (result == 0)
    {
        printf("Запис у root_copy.txt виконано успішно.\n");
    }
    else
    {
        printf("Запис у root_copy.txt не виконано. Недостатньо прав.\n");
    }

    printf("\n5. Повторний перегляд вмісту root_copy.txt:\n");
    system("cat root_copy.txt");

    printf("\n6. Спроба видалити root_copy.txt командою rm -f...\n");
    result = system("rm -f root_copy.txt");

    if (result == 0)
    {
        printf("Команда rm виконана.\n");
    }
    else
    {
        printf("Команду rm не вдалося виконати.\n");
    }

    printf("\n7. Перевірка файлів після видалення:\n");
    result = system("ls -l user_file.txt root_copy.txt 2>/dev/null");

    if (result != 0)
    {
        printf("Файл root_copy.txt більше не знайдено, тобто його було видалено.\n");
    }

    printf("\nВисновок: якщо файл належить root, звичайний користувач не може його змінити без прав запису. ");
    printf("Але якщо файл знаходиться у каталозі користувача, то користувач може видалити його, ");
    printf("бо має права на запис у своєму каталозі.\n");

    return 0;
}
