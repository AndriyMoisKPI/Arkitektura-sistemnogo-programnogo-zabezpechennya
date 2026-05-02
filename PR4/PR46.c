#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int main(void) {
    printf("Дослідження realloc(NULL, size) та realloc(ptr, 0)\n\n");

    errno = 0;

    char *p1 = realloc(NULL, 64);

    if (p1 == NULL) {
        printf("realloc(NULL, 64) повернув NULL. errno = %d (%s)\n",
               errno, strerror(errno));
    } else {
        strcpy(p1, "realloc(NULL, size) працює як malloc(size)");
        printf("realloc(NULL, 64) повернув адресу: %p\n", (void *)p1);
        printf("Вміст p1: %s\n", p1);
        free(p1);
    }

    printf("\n");

    char *p2 = malloc(64);

    if (p2 == NULL) {
        printf("malloc(64) не спрацював\n");
        return 1;
    }

    strcpy(p2, "Блок перед realloc(ptr, 0)");
    printf("Перед realloc(ptr, 0), p2 = %p\n", (void *)p2);
    printf("Вміст p2: %s\n", p2);

    errno = 0;

    char *p3 = realloc(p2, 0);

    printf("Після realloc(p2, 0), результат p3 = %p\n", (void *)p3);
    printf("errno = %d (%s)\n", errno, strerror(errno));

    /*
     * p2 після realloc(p2, 0) використовувати не можна,
     * оскільки блок уже міг бути звільнений.
     */

    return 0;
}
