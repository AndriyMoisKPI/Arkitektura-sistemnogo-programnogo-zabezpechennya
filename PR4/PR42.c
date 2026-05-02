#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

int main(void) {
    int negative = -100;
    int xa = 100000;
    int xb = 100000;
    int num = xa * xb;

    printf("Дослідження malloc() з від’ємним аргументом та переповненням int\n\n");

    printf("1) Від’ємне значення:\n");
    printf("negative = %d\n", negative);

    errno = 0;
    void *p1 = malloc(negative);

    if (p1 == NULL) {
        printf("malloc(%d) повернув NULL. errno = %d (%s)\n\n",
               negative, errno, strerror(errno));
    } else {
        printf("malloc(%d) повернув адресу: %p\n", negative, p1);
        free(p1);
    }

    printf("2) Переповнення signed int:\n");
    printf("xa = %d\n", xa);
    printf("xb = %d\n", xb);
    printf("num = xa * xb = %d\n", num);
    printf("INT_MAX = %d\n", INT_MAX);

    errno = 0;
    void *p2 = malloc(num);

    if (p2 == NULL) {
        printf("malloc(num) повернув NULL. errno = %d (%s)\n",
               errno, strerror(errno));
    } else {
        printf("malloc(num) повернув адресу: %p\n", p2);
        free(p2);
    }

    return 0;
}
