#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <errno.h>
#include <string.h>
#include <stddef.h>

int main(void) {
    printf("Дослідження максимального розміру malloc()\n\n");

    printf("sizeof(size_t) = %zu байт\n", sizeof(size_t));
    printf("SIZE_MAX = %zu\n", (size_t)SIZE_MAX);
    printf("PTRDIFF_MAX = %td\n\n", (ptrdiff_t)PTRDIFF_MAX);

    size_t tests[] = {
        1024ULL * 1024ULL,
        1024ULL * 1024ULL * 1024ULL,
        8ULL * 1024ULL * 1024ULL * 1024ULL,
        (size_t)PTRDIFF_MAX,
        (size_t)PTRDIFF_MAX + 1,
        (size_t)SIZE_MAX
    };

    const char *names[] = {
        "1 MB",
        "1 GB",
        "8 GB",
        "PTRDIFF_MAX",
        "PTRDIFF_MAX + 1",
        "SIZE_MAX"
    };

    for (int i = 0; i < 6; i++) {
        errno = 0;
        printf("Спроба malloc(%s) = %zu байт...\n", names[i], tests[i]);

        void *ptr = malloc(tests[i]);

        if (ptr == NULL) {
            printf("malloc повернув NULL. errno = %d (%s)\n\n", errno, strerror(errno));
        } else {
            printf("malloc повернув адресу: %p\n", ptr);
            free(ptr);
            printf("Пам’ять звільнено через free().\n\n");
        }
    }

    return 0;
}
