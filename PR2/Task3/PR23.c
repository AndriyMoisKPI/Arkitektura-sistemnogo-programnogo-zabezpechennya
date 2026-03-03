#include <stdio.h>
#include <stdlib.h>

int global_var = 10;
int global_uninit;

int main() {
    int local_var = 5;
    int *heap_var = malloc(sizeof(int));

    printf("Text segment: %p\n", main);
    printf("Data segment: %p\n", &global_var);
    printf("BSS segment: %p\n", &global_uninit);
    printf("Heap segment: %p\n", heap_var);
    printf("Stack segment: %p\n", &local_var);

    free(heap_var);
    return 0;
}
