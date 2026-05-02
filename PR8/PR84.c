#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }

    printf("Значення pid = %d\n", pid);

    if (pid == 0) {
        printf("Це дочірній процес. Його PID: %d, PID батька: %d\n", getpid(), getppid());
    } else {
        printf("Це батьківський процес. Його PID: %d, PID дитини: %d\n", getpid(), pid);
    }

    return 0;
}

