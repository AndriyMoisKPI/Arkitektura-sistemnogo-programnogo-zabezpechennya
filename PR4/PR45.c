#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdint.h>

int main(void) {
    size_t initial_size = 1024;
    size_t huge_size = (size_t)PTRDIFF_MAX;

    printf("Дослідження поведінки realloc() при помилці виділення пам’яті\n\n");

    char *ptr = malloc(initial_size);

    if (ptr == NULL) {
        printf("Початковий malloc() не спрацював: %s\n", strerror(errno));
        return 1;
    }

    strcpy(ptr, "Початкові дані у виділеному блоці");
    printf("Початковий блок виділено: %p\n", (void *)ptr);
    printf("Вміст блоку до realloc(): %s\n", ptr);

    errno = 0;
    printf("\nСпроба realloc() до дуже великого розміру: %zu байт\n", huge_size);

    char *newptr = realloc(ptr, huge_size);

    if (newptr == NULL) {
        printf("realloc() повернув NULL. errno = %d (%s)\n", errno, strerror(errno));
        printf("Старий вказівник ptr все ще дійсний: %p\n", (void *)ptr);
        printf("Вміст старого блоку після невдалого realloc(): %s\n", ptr);

        free(ptr);
        printf("Старий блок звільнено через free(ptr).\n");
    } else {
        printf("realloc() успішний, нова адреса: %p\n", (void *)newptr);
        free(newptr);
    }

    return 0;
}
