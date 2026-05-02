#include <stdio.h>
#include <signal.h>
#include <unistd.h>

volatile unsigned long long counter = 0;

void cpu_handler(int sig) {
    printf("\nОтримано сигнал %d. Ліміт CPU-часу досягнуто.\n", sig);
    printf("Кількість ітерацій до зупинки: %llu\n", counter);
    _exit(1);
}

int main(void) {
    signal(SIGXCPU, cpu_handler);

    printf("Програма запущена. Виконується нескінченний CPU-bound цикл.\n");
    printf("PID процесу: %d\n", getpid());

    while (1) {
        counter++;
    }

    return 0;
}
