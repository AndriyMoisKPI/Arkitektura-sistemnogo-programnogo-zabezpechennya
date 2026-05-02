#include <stdio.h>
#include <time.h>

long long milliseconds_diff(struct timespec start, struct timespec end) {
    long long seconds = end.tv_sec - start.tv_sec;
    long long nanoseconds = end.tv_nsec - start.tv_nsec;

    return seconds * 1000 + nanoseconds / 1000000;
}

int main(void) {
    struct timespec start;
    struct timespec end;
    volatile unsigned long long counter = 0;

    printf("Задача 9: вимірювання часу виконання фрагмента коду\n\n");

    clock_gettime(CLOCK_MONOTONIC, &start);

    for (unsigned long long i = 0; i < 500000000ULL; i++) {
        counter += i % 3;
    }

    clock_gettime(CLOCK_MONOTONIC, &end);

    printf("Результат обчислення counter = %llu\n", counter);
    printf("Час виконання фрагмента коду: %lld мс\n",
           milliseconds_diff(start, end));

    return 0;
}

