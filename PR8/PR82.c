#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "PR82_data.bin";

    unsigned char data[] = {4, 5, 2, 2, 3, 3, 7, 9, 1, 5};
    unsigned char buffer[4];

    int fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    ssize_t written = write(fd, data, sizeof(data));

    if (written == -1) {
        perror("write");
        close(fd);
        return 1;
    }

    printf("У файл записано байтів: %zd\n", written);

    off_t offset = lseek(fd, 3, SEEK_SET);

    if (offset == -1) {
        perror("lseek");
        close(fd);
        return 1;
    }

    printf("Позицію читання встановлено на зміщення: %ld\n", (long)offset);

    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));

    if (bytes_read == -1) {
        perror("read");
        close(fd);
        return 1;
    }

    printf("Прочитано байтів: %zd\n", bytes_read);

    printf("Вміст буфера: ");

    for (int i = 0; i < bytes_read; i++) {
        printf("%u", buffer[i]);

        if (i < bytes_read - 1) {
            printf(", ");
        }
    }

    printf("\n");

    close(fd);

    return 0;
}
