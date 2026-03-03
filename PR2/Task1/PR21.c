#include <stdio.h>
#include <time.h>
#include <limits.h>

int main() {
    printf("Size of time_t: %zu bytes\n", sizeof(time_t));

    if (sizeof(time_t) == 4) {
        printf("Likely 32-bit time_t\n");
        printf("Max value: %ld\n", (long)INT_MAX);
        printf("Overflow date: 19 January 2038\n");
    } else if (sizeof(time_t) == 8) {
        printf("Likely 64-bit time_t\n");
        printf("Very large range (~292 billion years)\n");
    }

    return 0;
}
