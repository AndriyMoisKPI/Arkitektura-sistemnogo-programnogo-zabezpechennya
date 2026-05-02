#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 50000
#define TESTS 5

int compare_ints(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

void fill_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }
}

void fill_reversed(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = n - i;
    }
}

void fill_random(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void fill_equal(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = 111;
    }
}

void fill_almost_sorted(int *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i;
    }

    for (int i = 0; i < n / 100; i++) {
        int a = rand() % n;
        int b = rand() % n;

        int temp = arr[a];
        arr[a] = arr[b];
        arr[b] = temp;
    }
}

int is_sorted(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (arr[i - 1] > arr[i]) {
            return 0;
        }
    }

    return 1;
}

double test_qsort(const char *name, void (*fill_func)(int *, int), int n) {
    int *arr = malloc(n * sizeof(int));

    if (arr == NULL) {
        perror("malloc");
        exit(1);
    }

    fill_func(arr, n);

    clock_t start = clock();

    qsort(arr, n, sizeof(int), compare_ints);

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%-25s | час: %.6f с | перевірка: %s\n",
           name,
           time_spent,
           is_sorted(arr, n) ? "OK" : "ERROR");

    free(arr);

    return time_spent;
}

void run_correctness_tests() {
    int test1[] = {5, 4, 3, 2, 1};
    int test2[] = {1, 1, 1, 1, 1};
    int test3[] = {10, -5, 0, 3, 2};
    int test4[] = {7};
    int test5[] = {2, 1};

    int *tests[] = {test1, test2, test3, test4, test5};
    int sizes[] = {5, 5, 5, 1, 2};

    printf("\nТести правильності qsort():\n");

    for (int i = 0; i < TESTS; i++) {
        qsort(tests[i], sizes[i], sizeof(int), compare_ints);

        printf("Тест %d: %s\n", i + 1, is_sorted(tests[i], sizes[i]) ? "OK" : "ERROR");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    printf("Дослідження qsort() для різних типів вхідних даних\n");
    printf("Кількість елементів у масиві: %d\n\n", SIZE);

    double t_sorted = test_qsort("Вже відсортований", fill_sorted, SIZE);
    double t_reversed = test_qsort("Зворотний порядок", fill_reversed, SIZE);
    double t_random = test_qsort("Випадкові дані", fill_random, SIZE);
    double t_equal = test_qsort("Однакові значення", fill_equal, SIZE);
    double t_almost = test_qsort("Майже відсортований", fill_almost_sorted, SIZE);

    double max_time = t_sorted;
    const char *worst = "Вже відсортований";

    if (t_reversed > max_time) {
        max_time = t_reversed;
        worst = "Зворотний порядок";
    }

    if (t_random > max_time) {
        max_time = t_random;
        worst = "Випадкові дані";
    }

    if (t_equal > max_time) {
        max_time = t_equal;
        worst = "Однакові значення";
    }

    if (t_almost > max_time) {
        max_time = t_almost;
        worst = "Майже відсортований";
    }

    printf("\nНайповільніший варіант у цьому запуску: %s\n", worst);
    printf("Час найповільнішого варіанта: %.6f с\n", max_time);

    run_correctness_tests();

    return 0;
}
