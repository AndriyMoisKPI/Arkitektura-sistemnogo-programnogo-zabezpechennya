#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile unsigned long depth = 0;

void handler(int sig) {
    printf("\nОтримано сигнал %d. Ймовірно, стек переповнено.\n", sig);
    printf("Остання глибина рекурсії: %lu\n", depth);
    _exit(1);
}

void recursive_function(void) {
    char buffer[1024];

    depth++;

    for (int i = 0; i < 1024; i++) {
        buffer[i] = (char)(i % 256);
    }

    if (depth % 100 == 0) {
        printf("Глибина рекурсії: %lu\n", depth);
        fflush(stdout);
    }

    recursive_function();
}

int main(void) {
    signal(SIGSEGV, handler);

    printf("Демонстрація обмеження max stack segment size\n");
    printf("Кожен рекурсивний виклик використовує приблизно 1 КБ стеку.\n");
    printf("Починаємо рекурсію...\n");

    recursive_function();

    return 0;
}
