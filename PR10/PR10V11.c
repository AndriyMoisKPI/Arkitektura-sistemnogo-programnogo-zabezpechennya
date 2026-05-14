#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    int status;

    printf("Варіант 11: виконання ls -l у дочірньому процесі через execlp()\n\n");

    printf("Батьківський процес: PID = %d\n", getpid());

    pid = fork();

    if (pid < 0)
    {
        perror("Помилка fork");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nДочірній процес створено.\n");
        printf("Дочірній процес: PID = %d\n", getpid());
        printf("PID батьківського процесу: %d\n", getppid());
        printf("\nДочірній процес виконує команду: ls -l\n\n");

        execlp("ls", "ls", "-l", NULL);

        perror("Помилка execlp");
        exit(1);
    }
    else
    {
        printf("Батьківський процес створив дочірній процес з PID = %d\n", pid);
        printf("Батьківський процес очікує завершення дочірнього процесу...\n\n");

        if (waitpid(pid, &status, 0) == -1)
        {
            perror("Помилка waitpid");
            return 1;
        }

        printf("\nДочірній процес завершив роботу.\n");

        if (WIFEXITED(status))
        {
            printf("Код завершення дочірнього процесу: %d\n", WEXITSTATUS(status));
        }
        else
        {
            printf("Дочірній процес завершився не звичайним способом.\n");
        }
    }

    printf("\nВисновок: команда ls -l була виконана у дочірньому процесі через execlp().\n");

    return 0;
}
