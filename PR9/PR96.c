#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int result;

    printf("Завдання 9.6: перегляд прав доступу та перевірка читання, запису і виконання\n\n");

    printf("1. Перегляд файлів у домашньому каталозі:\n");
    system("ls -l $HOME | head -n 10");

    printf("\n2. Перегляд файлів у /usr/bin:\n");
    system("ls -l /usr/bin | head -n 10");

    printf("\n3. Перегляд файлів у /etc:\n");
    system("ls -l /etc | head -n 10");

    printf("\n4. Створення тестового файлу у домашньому каталозі:\n");
    result = system("echo 'Тестовий файл користувача' > $HOME/pr96_user_file.txt");

    if (result == 0)
    {
        printf("Файл $HOME/pr96_user_file.txt створено.\n");
    }
    else
    {
        printf("Не вдалося створити тестовий файл.\n");
    }

    printf("\n5. Права доступу до тестового файлу:\n");
    system("ls -l $HOME/pr96_user_file.txt");

    printf("\n6. Спроба читання файлу з домашнього каталогу:\n");
    result = system("cat $HOME/pr96_user_file.txt");

    if (result == 0)
    {
        printf("Читання домашнього файлу виконано успішно.\n");
    }
    else
    {
        printf("Читання домашнього файлу не виконано.\n");
    }

    printf("\n7. Спроба запису у файл з домашнього каталогу:\n");
    result = system("echo 'Дописаний рядок' >> $HOME/pr96_user_file.txt");

    if (result == 0)
    {
        printf("Запис у домашній файл виконано успішно.\n");
    }
    else
    {
        printf("Запис у домашній файл не виконано.\n");
    }

    printf("\n8. Спроба виконання домашнього файлу без права x:\n");
    result = system("$HOME/pr96_user_file.txt");

    if (result == 0)
    {
        printf("Файл виконався.\n");
    }
    else
    {
        printf("Файл не виконався, бо немає права на виконання або це не програма.\n");
    }

    printf("\n9. Перевірка читання системного файлу /etc/passwd:\n");
    result = system("head -n 3 /etc/passwd");

    if (result == 0)
    {
        printf("Файл /etc/passwd можна читати звичайному користувачу.\n");
    }
    else
    {
        printf("Файл /etc/passwd прочитати не вдалося.\n");
    }

    printf("\n10. Перевірка запису у /etc/passwd через test -w:\n");
    result = system("test -w /etc/passwd");

    if (result == 0)
    {
        printf("Звичайний користувач має право запису в /etc/passwd.\n");
    }
    else
    {
        printf("Звичайний користувач не має права запису в /etc/passwd.\n");
    }

    printf("\n11. Перевірка читання закритого файлу /etc/shadow:\n");
    result = system("head -n 3 /etc/shadow");

    if (result == 0)
    {
        printf("Файл /etc/shadow вдалося прочитати.\n");
    }
    else
    {
        printf("Файл /etc/shadow прочитати не вдалося без sudo.\n");
    }

    printf("\n12. Перевірка виконання програми /usr/bin/ls:\n");
    result = system("/usr/bin/ls --version | head -n 1");

    if (result == 0)
    {
        printf("Файл /usr/bin/ls можна виконувати.\n");
    }
    else
    {
        printf("Файл /usr/bin/ls виконати не вдалося.\n");
    }

    printf("\n13. Перевірка запису у /usr/bin/ls через test -w:\n");
    result = system("test -w /usr/bin/ls");

    if (result == 0)
    {
        printf("Звичайний користувач має право запису в /usr/bin/ls.\n");
    }
    else
    {
        printf("Звичайний користувач не має права запису в /usr/bin/ls.\n");
    }

    printf("\n14. Очищення тестового файлу:\n");
    system("rm -f $HOME/pr96_user_file.txt");
    printf("Тестовий файл видалено.\n");

    printf("\nВисновок: програма показала різницю між правами доступу у домашньому каталозі, /usr/bin та /etc.\n");

    return 0;
}
