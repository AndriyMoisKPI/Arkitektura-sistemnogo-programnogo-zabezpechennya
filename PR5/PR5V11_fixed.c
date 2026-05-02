#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int id;
    double average;
    char name[32];
};

int main(void) {
    printf("Варіант 11: правильне використання sizeof(*ptr)\n\n");

    struct Student *student;

    printf("sizeof(student) = %zu байт\n", sizeof(student));
    printf("sizeof(*student) = %zu байт\n", sizeof(*student));

    /*
     * ПРАВИЛЬНО:
     * Виділяється пам’ять розміром sizeof(*student),
     * тобто розмір самої структури.
     */
    student = malloc(sizeof(*student));

    if (student == NULL) {
        printf("Помилка malloc()\n");
        return 1;
    }

    printf("Пам’ять виділено через malloc(sizeof(*student))\n");

    student->id = 11;
    student->average = 87.5;
    strcpy(student->name, "Moisienko Andrii");

    printf("id = %d\n", student->id);
    printf("average = %.2f\n", student->average);
    printf("name = %s\n", student->name);

    free(student);

    printf("Пам’ять звільнено\n");

    return 0;
}

