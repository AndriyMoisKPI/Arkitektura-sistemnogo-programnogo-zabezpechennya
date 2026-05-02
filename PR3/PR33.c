#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    FILE *file = fopen("dice_results.txt", "w");

    if (file == NULL) {
        perror("Не вдалося відкрити файл");
        return 1;
    }

    srand((unsigned int)time(NULL));

    printf("Імітація кидання шестигранного кубика.\n");
    printf("Результати записуються у файл dice_results.txt\n");

    for (long i = 1; ; i++) {
        int dice = rand() % 6 + 1;

        if (fprintf(file, "Кидок %ld: %d\n", i, dice) < 0) {
            printf("Помилка запису у файл: %s\n", strerror(errno));
            fclose(file);
            return 1;
        }

        if (fflush(file) == EOF) {
            printf("Досягнуто обмеження розміру файлу або сталася помилка запису.\n");
            printf("Опис помилки: %s\n", strerror(errno));
            fclose(file);
            return 1;
        }

        if (i % 100 == 0) {
            printf("Записано %ld результатів...\n", i);
        }
    }

    fclose(file);
    return 0;
}
