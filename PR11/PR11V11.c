#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

typedef struct
{
    int signal_number;
    const char *signal_name;
} ThreadSignalInfo;

void *signal_thread(void *arg)
{
    ThreadSignalInfo *info = (ThreadSignalInfo *)arg;

    sigset_t set;
    siginfo_t siginfo;

    sigemptyset(&set);
    sigaddset(&set, info->signal_number);

    printf("Потік для %s запущено. Очікується сигнал %d...\n",
           info->signal_name,
           info->signal_number);

    while (1)
    {
        int received_signal = sigwaitinfo(&set, &siginfo);

        if (received_signal == -1)
        {
            perror("Помилка sigwaitinfo");
            continue;
        }

        printf("\nПотік %s отримав сигнал.\n", info->signal_name);
        printf("Номер сигналу: %d\n", received_signal);
        printf("PID відправника: %ld\n", (long)siginfo.si_pid);
        printf("UID відправника: %ld\n", (long)siginfo.si_uid);

        if (received_signal == SIGUSR1)
        {
            printf("Оброблено SIGUSR1 у першому потоці.\n");
        }
        else if (received_signal == SIGUSR2)
        {
            printf("Оброблено SIGUSR2 у другому потоці.\n");
        }

        printf("----------------------------------------\n");
    }

    return NULL;
}

int main(void)
{
    pthread_t thread1;
    pthread_t thread2;

    ThreadSignalInfo info1 = { SIGUSR1, "SIGUSR1" };
    ThreadSignalInfo info2 = { SIGUSR2, "SIGUSR2" };

    sigset_t blocked_set;

    printf("Варіант 11: синхронна обробка сигналів у різних потоках через sigwaitinfo()\n\n");
    printf("PID процесу: %ld\n", (long)getpid());
    printf("Для перевірки відкрийте інший термінал і виконайте:\n");
    printf("kill -USR1 %ld\n", (long)getpid());
    printf("kill -USR2 %ld\n\n", (long)getpid());

    sigemptyset(&blocked_set);
    sigaddset(&blocked_set, SIGUSR1);
    sigaddset(&blocked_set, SIGUSR2);

    if (pthread_sigmask(SIG_BLOCK, &blocked_set, NULL) != 0)
    {
        perror("Помилка pthread_sigmask");
        return 1;
    }

    if (pthread_create(&thread1, NULL, signal_thread, &info1) != 0)
    {
        perror("Помилка pthread_create для SIGUSR1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, signal_thread, &info2) != 0)
    {
        perror("Помилка pthread_create для SIGUSR2");
        return 1;
    }

    printf("Основний потік працює. Натисніть Ctrl+C для завершення програми.\n\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
