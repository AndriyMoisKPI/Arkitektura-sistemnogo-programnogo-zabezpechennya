#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *pipe;
    char buffer[256];

    printf("Задача 1: передавання виводу rwho до more через popen()\n\n");

    /*
     * Команда rwho 2>/dev/null | more:
     * rwho виводить інформацію про користувачів у мережі,
     * more посторінково показує результат.
     */
    pipe = popen("rwho 2>/dev/null | more", "r");

    if (pipe == NULL) {
        perror("popen");
        return 1;
    }

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        printf("%s", buffer);
    }

    int status = pclose(pipe);

    printf("\nКоманда завершилася зі статусом: %d\n", status);

    return 0;
}
