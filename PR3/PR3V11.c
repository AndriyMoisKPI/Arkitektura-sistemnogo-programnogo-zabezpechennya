#include <stdio.h>
#include <stdlib.h>

void recursive_algorithm(int current, int max_depth) {
    char buffer[1024];

    for (int i = 0; i < 1024; i++) {
        buffer[i] = (char)(i % 256);
    }

    if (buffer[0] == -1) {
        printf("Impossible value\n");
    }

    if (current >= max_depth) {
        printf("Досягнуто заданої глибини рекурсії: %d\n", current);
        return;
    }

    if (current % 500 == 0) {
        printf("Поточна глибина рекурсії: %d\n", current);
        fflush(stdout);
    }

    recursive_algorithm(current + 1, max_depth);
}

int main(int argc, char *argv[]) {
    int max_depth;

    if (argc != 2) {
        printf("Використання: %s <глибина_рекурсії>\n", argv[0]);
        return 1;
    }

    max_depth = atoi(argv[1]);

    if (max_depth <= 0) {
        printf("Глибина рекурсії має бути додатним числом.\n");
        return 1;
    }

    printf("Дослідження впливу ulimit -s на рекурсивний алгоритм\n");
    printf("Задана глибина рекурсії: %d\n", max_depth);
    printf("Кожен рекурсивний виклик використовує приблизно 1 КБ стеку.\n");

    recursive_algorithm(1, max_depth);

    printf("Програма завершилася успішно.\n");
    return 0;
}
