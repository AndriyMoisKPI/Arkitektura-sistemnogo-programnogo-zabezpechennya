#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define COUNT 10

double random_0_1(void) {
    return (double)rand() / (double)RAND_MAX;
}

double random_0_n(double n) {
    return random_0_1() * n;
}

int main(void) {
    double n;

    unsigned int seed = (unsigned int)time(NULL) ^ (unsigned int)getpid();
    srand(seed);

    printf("Задача 10: генерація випадкових чисел з плаваючою комою\n\n");
    printf("Seed = %u\n\n", seed);

    printf("Введіть значення n: ");
    if (scanf("%lf", &n) != 1 || n < 0.0) {
        printf("Помилка: n має бути невід’ємним числом.\n");
        return 1;
    }

    printf("\n(a) Випадкові числа у діапазоні від 0.0 до 1.0:\n");
    for (int i = 0; i < COUNT; i++) {
        printf("%.6f\n", random_0_1());
    }

    printf("\n(b) Випадкові числа у діапазоні від 0.0 до %.2f:\n", n);
    for (int i = 0; i < COUNT; i++) {
        printf("%.6f\n", random_0_n(n));
    }

    return 0;
}
