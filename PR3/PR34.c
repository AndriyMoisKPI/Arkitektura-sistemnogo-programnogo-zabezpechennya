#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t cpu_limit_reached = 0;

void cpu_handler(int sig) {
    (void)sig;
    cpu_limit_reached = 1;
}

int already_exists(int arr[], int count, int value) {
    for (int i = 0; i < count; i++) {
        if (arr[i] == value) {
            return 1;
        }
    }
    return 0;
}

void generate_unique_numbers(int arr[], int count, int max_value) {
    int generated = 0;

    while (generated < count) {
        int value = rand() % max_value + 1;

        if (!already_exists(arr, generated, value)) {
            arr[generated] = value;
            generated++;
        }
    }
}

void print_numbers(const char *title, int arr[], int count) {
    printf("%s", title);

    for (int i = 0; i < count; i++) {
        printf("%d ", arr[i]);
    }

    printf("\n");
}

int main(void) {
    signal(SIGXCPU, cpu_handler);
    srand((unsigned int)time(NULL));

    printf("Імітація лотереї з обмеженням CPU-часу.\n");
    printf("Програма генерує 7 чисел із 49 та 6 чисел із 36.\n");

    unsigned long long attempt = 0;

    while (!cpu_limit_reached) {
        int first_set[7];
        int second_set[6];

        generate_unique_numbers(first_set, 7, 49);
        generate_unique_numbers(second_set, 6, 36);

        attempt++;

        if (attempt % 100000 == 0) {
            printf("Згенеровано наборів: %llu\n", attempt);
            print_numbers("7 із 49: ", first_set, 7);
            print_numbers("6 із 36: ", second_set, 6);
            fflush(stdout);
        }
    }

    printf("\nДосягнуто ліміту CPU-часу.\n");
    printf("Усього згенеровано наборів: %llu\n", attempt);

    return 0;
}
