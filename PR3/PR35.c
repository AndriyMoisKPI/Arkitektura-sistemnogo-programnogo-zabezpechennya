#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    FILE *src;
    FILE *dst;
    char buffer[BUFFER_SIZE];
    size_t bytes_read;

    if (argc != 3) {
        printf("Program need two arguments\n");
        return 1;
    }

    src = fopen(argv[1], "rb");
    if (src == NULL) {
        printf("Cannot open file %s for reading\n", argv[1]);
        return 1;
    }

    dst = fopen(argv[2], "wb");
    if (dst == NULL) {
        printf("Cannot open file %s for writing\n", argv[2]);
        fclose(src);
        return 1;
    }

    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, src)) > 0) {
        size_t bytes_written = fwrite(buffer, 1, bytes_read, dst);

        if (bytes_written < bytes_read) {
            printf("Write error while copying file: %s\n", strerror(errno));
            printf("Possible reason: file size limit exceeded\n");
            fclose(src);
            fclose(dst);
            return 1;
        }

        if (fflush(dst) == EOF) {
            printf("Flush error while copying file: %s\n", strerror(errno));
            printf("Possible reason: file size limit exceeded\n");
            fclose(src);
            fclose(dst);
            return 1;
        }
    }

    if (ferror(src)) {
        printf("Read error while copying file: %s\n", strerror(errno));
        fclose(src);
        fclose(dst);
        return 1;
    }

    fclose(src);
    fclose(dst);

    printf("File copied successfully\n");
    return 0;
}
