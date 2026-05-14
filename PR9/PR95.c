#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;

    printf("Завдання 9.5: перевірка доступу після chown і chmod\n\n");

    printf("1. Створення тимчасового файлу від імені звичайного користувача...\n");
    result = system("echo 'Початковий текст у тимчасовому файлі' > temp_access_file.txt");

    if (result != 0)
    {
        printf("Помилка створення файлу.\n");
        return 1;
    }

    printf("Файл temp_access_file.txt створено.\n\n");

    printf("2. Початкові права доступу:\n");
    system("ls -l temp_access_file.txt");

    printf("\n3. Перевірка читання файлу звичайним користувачем:\n");
    result = system("cat temp_access_file.txt");

    if (result == 0)
    {
        printf("Читання виконано успішно.\n");
    }
    else
    {
        printf("Читання виконати не вдалося.\n");
    }

    printf("\n4. Перевірка запису у файл звичайним користувачем:\n");
    result = system("echo 'Дописано звичайним користувачем' >> temp_access_file.txt");

    if (result == 0)
    {
        printf("Запис виконано успішно.\n");
    }
    else
    {
        printf("Запис виконати не вдалося.\n");
    }

    printf("\n5. Зміна власника файлу на root через sudo chown...\n");
    result = system("sudo chown root:root temp_access_file.txt");

    if (result != 0)
    {
        printf("Не вдалося змінити власника файлу.\n");
        return 1;
    }

    printf("Власника файлу змінено на root.\n");

    printf("\n6. Встановлення прав 644 через sudo chmod...\n");
    system("sudo chmod 644 temp_access_file.txt");
    system("ls -l temp_access_file.txt");

    printf("\n7. Перевірка читання при правах 644:\n");
    result = system("cat temp_access_file.txt");

    if (result == 0)
    {
        printf("Читання виконано успішно, бо для інших користувачів є право r.\n");
    }
    else
    {
        printf("Читання виконати не вдалося.\n");
    }

    printf("\n8. Перевірка запису при правах 644:\n");
    result = system("echo 'Спроба запису при 644' >> temp_access_file.txt");

    if (result == 0)
    {
        printf("Запис виконано успішно.\n");
    }
    else
    {
        printf("Запис виконати не вдалося, бо файл належить root і немає права w для інших.\n");
    }

    printf("\n9. Встановлення прав 666 через sudo chmod...\n");
    system("sudo chmod 666 temp_access_file.txt");
    system("ls -l temp_access_file.txt");

    printf("\n10. Перевірка запису при правах 666:\n");
    result = system("echo 'Запис при правах 666' >> temp_access_file.txt");

    if (result == 0)
    {
        printf("Запис виконано успішно, бо право запису є для всіх користувачів.\n");
    }
    else
    {
        printf("Запис виконати не вдалося.\n");
    }

    printf("\n11. Встановлення прав 600 через sudo chmod...\n");
    system("sudo chmod 600 temp_access_file.txt");
    system("ls -l temp_access_file.txt");

    printf("\n12. Перевірка читання при правах 600:\n");
    result = system("cat temp_access_file.txt");

    if (result == 0)
    {
        printf("Читання виконано успішно.\n");
    }
    else
    {
        printf("Читання виконати не вдалося, бо файл належить root і доступ для інших закритий.\n");
    }

    printf("\n13. Очищення: видалення файлу через sudo...\n");
    system("sudo rm -f temp_access_file.txt");

    printf("\nВисновок: доступ до файлу залежить від його власника та встановлених прав chmod.\n");

    return 0;
}
