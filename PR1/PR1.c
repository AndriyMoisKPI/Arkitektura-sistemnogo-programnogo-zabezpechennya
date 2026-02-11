#include <stdio.h>
#include <string.h>

#define MAX 100
#define FILENAME "students.txt"

typedef struct {
    int day, month, year;
} Date;

typedef struct {
    char region[50];
    char city[50];
    char street[50];
    int house;
    int apartment;
} Address;

typedef struct {
    char surname[50];
    char name[50];
    char patronymic[50];
    Date birth;
    Address address;
} Student;

Student db[MAX];
int count = 0;

void clearInput() {
    while (getchar() != '\n');
}

int isLeap(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int validDate(Date d) {
    int days[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    if (d.year < 1900 || d.year > 2025) return 0;
    if (d.month < 1 || d.month > 12) return 0;
    if (isLeap(d.year)) days[1] = 29;
    return d.day >= 1 && d.day <= days[d.month - 1];
}

void loadFromFile() {
    FILE *f = fopen(FILENAME, "rb");
    if (!f) return; 
    fread(&count, sizeof(int), 1, f);
    fread(db, sizeof(Student), count, f);
    fclose(f);
}

void saveToFile() {
    FILE *f = fopen(FILENAME, "wb");
    if (!f) {
        printf("Помилка збереження файлу\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, f);
    fwrite(db, sizeof(Student), count, f);
    fclose(f);
}

void printStudent(int i) {
    Student s = db[i];
    printf("\n[%d] %s %s %s\n", i + 1, s.surname, s.name, s.patronymic);
    printf("    %02d.%02d.%d\n", s.birth.day, s.birth.month, s.birth.year);
    printf("    %s обл., %s, вул. %s, буд. %d, кв. %d\n",
           s.address.region,
           s.address.city,
           s.address.street,
           s.address.house,
           s.address.apartment);
}

void printShortList() {
    for (int i = 0; i < count; i++)
        printf("[%d] %s %s %s\n", i + 1, db[i].surname, db[i].name, db[i].patronymic);
}

void addStudent() {
    if (count >= MAX) {
        printf("База переповнена\n");
        return;
    }

    Student *s = &db[count];

    printf("Прізвище: ");
    fgets(s->surname, 50, stdin); strtok(s->surname, "\n");

    printf("Ім'я: ");
    fgets(s->name, 50, stdin); strtok(s->name, "\n");

    printf("По батькові: ");
    fgets(s->patronymic, 50, stdin); strtok(s->patronymic, "\n");

    do {
        printf("Дата народження (дд мм рррр): ");
        scanf("%d %d %d", &s->birth.day, &s->birth.month, &s->birth.year);
        clearInput();
        if (!validDate(s->birth))
            printf("Невірна дата. Спробуйте ще раз.\n");
    } while (!validDate(s->birth));

    printf("Область: ");
    fgets(s->address.region, 50, stdin); strtok(s->address.region, "\n");

    printf("Місто/село: ");
    fgets(s->address.city, 50, stdin); strtok(s->address.city, "\n");

    printf("Вулиця: ");
    fgets(s->address.street, 50, stdin); strtok(s->address.street, "\n");

    printf("Будинок: ");
    scanf("%d", &s->address.house);

    printf("Квартира: ");
    scanf("%d", &s->address.apartment);
    clearInput();

    count++;
    saveToFile();
    printf("Студента додано\n");
}

void listStudents() {
    if (count == 0) {
        printf("База порожня\n");
        return;
    }
    for (int i = 0; i < count; i++)
        printStudent(i);
}

void editStudent() {
    int n, c;

    if (count == 0) {
        printf("База порожня\n");
        return;
    }

    printf("\nСписок студентів:\n");
    printShortList();

    printf("\nОберіть номер студента для редагування: ");
    scanf("%d", &n);
    clearInput();

    if (n < 1 || n > count) {
        printf("Невірний номер\n");
        return;
    }

    Student *s = &db[n - 1];

    do {
        printf("\nРедагування студента: %s %s %s\n", s->surname, s->name, s->patronymic);

        printf("\nОберіть поле для редагування:\n");
        printf("1. Прізвище\n2. Ім'я\n3. По батькові\n");
        printf("4. Дата народження\n5. Область\n6. Місто/село\n");
        printf("7. Вулиця\n8. Будинок\n9. Квартира\n0. Завершити редагування\n");
        printf("Ваш вибір: ");

        scanf("%d", &c);
        clearInput();

        switch (c) {
            case 1:
                printf("Введіть нове прізвище: ");
                fgets(s->surname, 50, stdin);
                strtok(s->surname, "\n");
                break;
            case 2:
                printf("Введіть нове ім'я: ");
                fgets(s->name, 50, stdin);
                strtok(s->name, "\n");
                break;
            case 3:
                printf("Введіть нове по батькові: ");
                fgets(s->patronymic, 50, stdin);
                strtok(s->patronymic, "\n");
                break;
            case 4:
                do {
                    printf("Введіть нову дату (дд мм рррр): ");
                    scanf("%d %d %d", &s->birth.day, &s->birth.month, &s->birth.year);
                    clearInput();
                } while (!validDate(s->birth));
                break;
            case 5:
                printf("Введіть нову область: ");
                fgets(s->address.region, 50, stdin);
                strtok(s->address.region, "\n");
                break;
            case 6:
                printf("Введіть нове місто/село: ");
                fgets(s->address.city, 50, stdin);
                strtok(s->address.city, "\n");
                break;
            case 7:
                printf("Введіть нову вулицю: ");
                fgets(s->address.street, 50, stdin);
                strtok(s->address.street, "\n");
                break;
            case 8:
                printf("Введіть новий номер будинку: ");
                scanf("%d", &s->address.house);
                clearInput();
                break;
            case 9:
                printf("Введіть новий номер квартири: ");
                scanf("%d", &s->address.apartment);
                clearInput();
                break;
        }

    } while (c != 0);

    saveToFile();
    printf("Редагування завершено\n");
}

void deleteStudent() {
    int n;

    if (count == 0) {
        printf("База порожня\n");
        return;
    }

    printf("\nСписок студентів:\n");
    printShortList();

    printf("\nОберіть номер студента для видалення: ");
    scanf("%d", &n);
    clearInput();

    if (n < 1 || n > count) {
        printf("Невірний номер\n");
        return;
    }

    for (int i = n - 1; i < count - 1; i++)
        db[i] = db[i + 1];

    count--;
    saveToFile();
    printf("Студента видалено\n");
}

void searchAny() {
    char key[50];
    printf("Введіть частину ПІБ або адреси для пошуку: ");
    fgets(key, 50, stdin);
    strtok(key, "\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (strstr(db[i].surname, key) || strstr(db[i].name, key) ||
            strstr(db[i].patronymic, key) || strstr(db[i].address.region, key) ||
            strstr(db[i].address.city, key) || strstr(db[i].address.street, key)) {
            printStudent(i);
            found = 1;
        }
    }
    if (!found)
        printf("За цим запитом нічого не знайдено\n");
}

int main() {
    loadFromFile();

    int c;
    do {
        printf("\n=== БАЗА СТУДЕНТІВ ===\n");
        printf("1. Додати студента\n");
        printf("2. Показати всіх студентів\n");
        printf("3. Редагувати студента\n");
        printf("4. Видалити студента\n");
        printf("5. Пошук\n");
        printf("0. Вихід\n");
        printf("Ваш вибір: ");

        scanf("%d", &c);
        clearInput();

        switch(c) {
            case 1: addStudent(); break;
            case 2: listStudents(); break;
            case 3: editStudent(); break;
            case 4: deleteStudent(); break;
            case 5: searchAny(); break;
        }

    } while(c != 0);

    saveToFile(); 
    printf("До побачення!\n");
    return 0;
}

