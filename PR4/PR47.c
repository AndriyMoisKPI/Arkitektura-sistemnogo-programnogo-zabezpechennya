#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

struct sbar {
    int id;
    double value;
    char name[32];
};

int main(void) {
    struct sbar *ptr;
    struct sbar *newptr;

    printf("Дослідження calloc(), realloc() та reallocarray()\n\n");

    ptr = calloc(1000, sizeof(struct sbar));

    if (ptr == NULL) {
        printf("calloc() не спрацював: %s\n", strerror(errno));
        return 1;
    }

    printf("calloc(1000, sizeof(struct sbar)) успішний\n");
    printf("Адреса ptr: %p\n", (void *)ptr);

    for (int i = 0; i < 1000; i++) {
        ptr[i].id = i;
        ptr[i].value = i * 1.5;
        snprintf(ptr[i].name, sizeof(ptr[i].name), "item_%d", i);
    }

    errno = 0;

    newptr = reallocarray(ptr, 500, sizeof(struct sbar));

    if (newptr == NULL) {
        printf("reallocarray() не спрацював: %s\n", strerror(errno));
        free(ptr);
        return 1;
    }

    ptr = newptr;

    printf("reallocarray(ptr, 500, sizeof(struct sbar)) успішний\n");
    printf("Нова адреса ptr: %p\n", (void *)ptr);
    printf("Приклад елемента після зменшення: id=%d, value=%.2f, name=%s\n",
           ptr[10].id, ptr[10].value, ptr[10].name);

    free(ptr);
    printf("Пам’ять звільнено через free(ptr)\n");

    return 0;
}

