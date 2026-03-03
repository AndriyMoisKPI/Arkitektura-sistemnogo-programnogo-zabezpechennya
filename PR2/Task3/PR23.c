#include <stdio.h>
#include <stdlib.h>

int global_init = 10;     // DATA
int global_uninit;        // BSS

void big_stack() {
    int big_array1[10000];
    int big_array2[10000];

    printf("Inside big_stack(): %p %p\n", &big_array1, &big_array2);
}

int main() {
    int local_var = 5;          // STACK
    int *heap_var = malloc(4);  // HEAP

    printf("Text segment (main):      %p\n", main);
    printf("Data segment:             %p\n", &global_init);
    printf("BSS segment:              %p\n", &global_uninit);
    printf("Heap segment:             %p\n", heap_var);
    printf("Stack top (local_var):    %p\n", &local_var);

    big_stack();   // ← ОСЬ ТУТ викликаємо функцію

    free(heap_var);
    return 0;
}
