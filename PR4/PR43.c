#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void) {
    printf("Дослідження malloc(0)\n\n");

    errno = 0;

    void *ptr = malloc(0);

    if (ptr == NULL) {
        printf("malloc(0) повернув NULL\n");
        printf("errno = %d (%s)\n", errno, strerror(errno));
    } else {
        printf("malloc(0) повернув не NULL: %p\n", ptr);
        printf("Такий вказівник не можна використовувати для запису даних,\n");
        printf("але його можна передати у free().\n");
    }

    free(ptr);

    printf("free(ptr) виконано успішно.\n");

    return 0;
}
