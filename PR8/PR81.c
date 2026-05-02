#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main() {
    int fd[2];

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    int read_fd = fd[0];
    int write_fd = fd[1];

    int flags = fcntl(write_fd, F_GETFL, 0);

    if (flags == -1) {
        perror("fcntl F_GETFL");
        return 1;
    }

    if (fcntl(write_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        return 1;
    }

    char buffer[8192];
    memset(buffer, 'A', sizeof(buffer));

    ssize_t count;

    while (1) {
        count = write(write_fd, buffer, sizeof(buffer));

        if (count == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                printf("Pipe заповнено. Подальший запис неможливий.\n");
                break;
            } else {
                perror("write");
                return 1;
            }
        }
    }

    char small_buffer[4096];

    ssize_t read_count = read(read_fd, small_buffer, sizeof(small_buffer));

    if (read_count == -1) {
        perror("read");
        return 1;
    }

    printf("З pipe прочитано %zd байт.\n", read_count);

    ssize_t nbytes = sizeof(buffer);

    count = write(write_fd, buffer, nbytes);

    if (count == -1) {
        perror("write after read");
        return 1;
    }

    printf("Було запрошено записати: %zd байт\n", nbytes);
    printf("Фактично записано:      %zd байт\n", count);

    if (count != nbytes) {
        printf("Висновок: write() записав не всі байти.\n");
    } else {
        printf("Висновок: write() записав усі байти.\n");
    }

    close(read_fd);
    close(write_fd);

    return 0;
}
