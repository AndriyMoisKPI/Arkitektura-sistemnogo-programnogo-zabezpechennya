#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *ptr = NULL;
    int iterations = 3;

    printf("Правильний варіант: після free(ptr) виконується ptr = NULL\n\n");

    for (int i = 0; i < iterations; i++) {
        printf("Ітерація %d\n", i + 1);

        if (!ptr) {
            ptr = malloc(32);
            if (ptr == NULL) {
                printf("Помилка malloc()\n");
                return 1;
            }
            printf("malloc виконано, ptr = %p\n", (void *)ptr);
        }

        strcpy(ptr, "Hello from malloc");
        printf("Вміст ptr: %s\n", ptr);

        free(ptr);
        ptr = NULL;

        printf("free(ptr) виконано, після цього ptr = NULL\n\n");
    }

    return 0;
}
