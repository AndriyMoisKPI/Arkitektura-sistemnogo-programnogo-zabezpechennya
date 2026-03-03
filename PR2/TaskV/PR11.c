#include <stdio.h>
#include <stdlib.h>

int global_var = 42;

int main() {
    int local_var = 10;
    int *heap_var = malloc(sizeof(int));

    printf("Address of main:        %p\n", main);
    printf("Address of global_var:  %p\n", &global_var);
    printf("Address of heap_var:    %p\n", heap_var);
    printf("Address of local_var:   %p\n", &local_var);

    free(heap_var);
    return 0;
}
