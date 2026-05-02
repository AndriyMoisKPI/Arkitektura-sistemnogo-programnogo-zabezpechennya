#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_COMMANDS 2048
#define MAX_NAME 128
#define MAX_LINE 1024

typedef struct {
    char name[MAX_NAME];
    int count;
} CommandStat;

void trim_newline(char *str) {
    size_t len = strlen(str);

    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void extract_command_name(const char *line, char *command) {
    const char *p = line;

    /*
     * Рядок history має вигляд:
     *   123  gcc -Wall file.c -o file
     * Тому спочатку пропускаємо номер команди та пробіли.
     */
    while (isdigit((unsigned char)*p) || isspace((unsigned char)*p)) {
        p++;
    }

    if (*p == '\0') {
        command[0] = '\0';
        return;
    }

    int i = 0;

    while (*p != '\0' && !isspace((unsigned char)*p) && i < MAX_NAME - 1) {
        command[i++] = *p++;
    }

    command[i] = '\0';
}

int find_command(CommandStat stats[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(stats[i].name, name) == 0) {
            return i;
        }
    }

    return -1;
}

int compare_by_count_then_name(const void *a, const void *b) {
    const CommandStat *cmd1 = (const CommandStat *)a;
    const CommandStat *cmd2 = (const CommandStat *)b;

    if (cmd1->count != cmd2->count) {
        return cmd1->count - cmd2->count;
    }

    return strcmp(cmd1->name, cmd2->name);
}

int main(void) {
    char line[MAX_LINE];
    CommandStat stats[MAX_COMMANDS];
    int command_count = 0;

    printf("Варіант 11: найменш використовувані команди з history\n\n");
    printf("Програма не читає .bash_history напряму.\n");
    printf("Історія передається через pipe: history | ./PR7V11\n\n");

    while (fgets(line, sizeof(line), stdin) != NULL) {
        char command[MAX_NAME];

        trim_newline(line);
        extract_command_name(line, command);

        if (command[0] == '\0') {
            continue;
        }

        int index = find_command(stats, command_count, command);

        if (index >= 0) {
            stats[index].count++;
        } else {
            if (command_count >= MAX_COMMANDS) {
                printf("Досягнуто максимальну кількість команд.\n");
                break;
            }

            strncpy(stats[command_count].name, command, MAX_NAME - 1);
            stats[command_count].name[MAX_NAME - 1] = '\0';
            stats[command_count].count = 1;
            command_count++;
        }
    }

    if (command_count == 0) {
        printf("Дані history не були передані.\n");
        printf("Запустіть програму так: history | ./PR7V11\n");
        return 0;
    }

    qsort(stats, command_count, sizeof(CommandStat), compare_by_count_then_name);

    printf("Усього різних команд знайдено: %d\n\n", command_count);
    printf("Найменш використовувані команди:\n");

    int limit = command_count < 10 ? command_count : 10;

    for (int i = 0; i < limit; i++) {
        printf("%-20s %d раз(ів)\n", stats[i].name, stats[i].count);
    }

    return 0;
}

