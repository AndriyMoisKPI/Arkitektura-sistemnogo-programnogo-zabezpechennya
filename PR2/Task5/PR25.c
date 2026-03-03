#include <stdio.h>

void test() {
    int local_array1[10000];
    int local_array2[10000] = {1};
}

int main() {
    test();
    printf("Hello\n");
    return 0;
}
