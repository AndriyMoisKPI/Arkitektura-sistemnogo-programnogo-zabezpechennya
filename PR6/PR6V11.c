#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#define PROCESS_COUNT 4
#define WORK_SECONDS 8

unsigned long long cpu_bound_work(int seconds) {
    unsigned long long counter = 0;
    time_t start = time(NULL);

    while (time(NULL) - start < seconds) {
        counter++;

        /*
         * Невелика штучна операція, щоб цикл не був повністю порожнім.
         */
        double x = counter * 3.14159;
        x = x / 2.71828;

        if (x < 0) {
            printf("Impossible\n");
        }
    }

    return counter;
}

int main(void) {
    pid_t pids[PROCESS_COUNT];

    printf("Практична робота 6, варіант 11\n");
    printf("Дослідження CPU-bound процесів та впливу nice() на планувальник\n\n");

    for (int i = 0; i < PROCESS_COUNT; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            int nice_value = 0;

            /*
             * Для частини процесів змінюємо nice.
             * Чим більше nice, тим нижчий пріоритет процесу.
             */
            if (i == 1) {
                nice_value = 5;
            } else if (i == 2) {
                nice_value = 10;
            } else if (i == 3) {
                nice_value = 15;
            }

            errno = 0;
            int result = nice(nice_value);

            if (result == -1 && errno != 0) {
                printf("Процес %d: помилка nice(%d): %s\n",
                       i, nice_value, strerror(errno));
            }

            int actual_nice = getpriority(PRIO_PROCESS, 0);

            printf("Процес %d стартував. PID=%d, nice=%d\n",
                   i, getpid(), actual_nice);
            fflush(stdout);

            unsigned long long iterations = cpu_bound_work(WORK_SECONDS);

            printf("Процес %d завершився. PID=%d, nice=%d, ітерацій=%llu\n",
                   i, getpid(), actual_nice, iterations);
            fflush(stdout);

            exit(0);
        } else {
            pids[i] = pid;
        }
    }

    for (int i = 0; i < PROCESS_COUNT; i++) {
        waitpid(pids[i], NULL, 0);
    }

    printf("\nУсі процеси завершилися.\n");

    return 0;
}
