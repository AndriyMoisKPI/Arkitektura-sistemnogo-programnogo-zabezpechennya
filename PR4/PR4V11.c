#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define BLOCK_SIZE_MB 10
#define MAX_BLOCKS 10000

int main(void) {
    void *blocks[MAX_BLOCKS];
    size_t block_size = BLOCK_SIZE_MB * 1024 * 1024;
    int count = 0;

    printf("Варіант 11: контрольований OOM через ulimit та malloc()\n");
    printf("Розмір одного блоку: %d МБ\n", BLOCK_SIZE_MB);
    printf("Програма буде виділяти пам’ять блоками, поки malloc() не поверне NULL.\n\n");

    for (int i = 0; i < MAX_BLOCKS; i++) {
        errno = 0;

        blocks[i] = malloc(block_size);

        if (blocks[i] == NULL) {
            printf("malloc() повернув NULL на ітерації %d\n", i + 1);
            printf("errno = %d (%s)\n", errno, strerror(errno));
            printf("Успішно виділено блоків: %d\n", count);
            printf("Загальний обсяг успішно виділеної пам’яті: %zu МБ\n",
                   (size_t)count * BLOCK_SIZE_MB);
            break;
        }

        /*
         * Записуємо хоча б один байт у блок, щоб пам’ять реально торкалась.
         * Без цього Linux може лише зарезервувати віртуальну пам’ять.
         */
        ((char *)blocks[i])[0] = 1;

        count++;

        printf("Виділено блок %d, загалом приблизно %zu МБ\n",
               count, (size_t)count * BLOCK_SIZE_MB);

        usleep(100000);
    }

    printf("\nЗвільнення пам’яті...\n");

    for (int i = 0; i < count; i++) {
        free(blocks[i]);
    }

    printf("Пам’ять звільнено. Програма завершена.\n");

    return 0;
}
