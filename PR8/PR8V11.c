#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 30

typedef struct {
    int key;
    int original_index;
    char name[16];
} Item;

int unstable_compare(const void *a, const void *b) {
    const Item *x = (const Item *)a;
    const Item *y = (const Item *)b;

    if (x->key < y->key) {
        return -1;
    }

    if (x->key > y->key) {
        return 1;
    }

    /*
       Нестабільне порівняння:
       якщо ключі однакові, порядок визначається не тільки ключем,
       а ще й початковим індексом у зворотному напрямку.
    */
    if (x->original_index > y->original_index) {
        return -1;
    }

    if (x->original_index < y->original_index) {
        return 1;
    }

    return 0;
}

void swap_items(Item *a, Item *b) {
    Item temp = *a;
    *a = *b;
    *b = temp;
}

void my_qsort(Item *arr, int left, int right) {
    int i = left;
    int j = right;
    Item pivot = arr[(left + right) / 2];

    while (i <= j) {
        while (unstable_compare(&arr[i], &pivot) < 0) {
            i++;
        }

        while (unstable_compare(&arr[j], &pivot) > 0) {
            j--;
        }

        if (i <= j) {
            swap_items(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }

    if (left < j) {
        my_qsort(arr, left, j);
    }

    if (i < right) {
        my_qsort(arr, i, right);
    }
}

void fill_items(Item *arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i].key = i % 5;
        arr[i].original_index = i;
        snprintf(arr[i].name, sizeof(arr[i].name), "obj_%02d", i);
    }
}

void print_items(const char *title, Item *arr, int n) {
    printf("\n%s\n", title);
    printf("----------------------------------------\n");
    printf(" key | original_index | name\n");
    printf("----------------------------------------\n");

    for (int i = 0; i < n; i++) {
        printf(" %3d | %14d | %s\n",
               arr[i].key,
               arr[i].original_index,
               arr[i].name);
    }
}

int is_sorted(Item *arr, int n) {
    for (int i = 1; i < n; i++) {
        if (unstable_compare(&arr[i - 1], &arr[i]) > 0) {
            return 0;
        }
    }

    return 1;
}

int arrays_equal(Item *a, Item *b, int n) {
    for (int i = 0; i < n; i++) {
        if (a[i].key != b[i].key ||
            a[i].original_index != b[i].original_index ||
            strcmp(a[i].name, b[i].name) != 0) {
            return 0;
        }
    }

    return 1;
}

int main() {
    Item original[SIZE];
    Item system_sorted[SIZE];
    Item custom_sorted[SIZE];

    fill_items(original, SIZE);

    memcpy(system_sorted, original, sizeof(original));
    memcpy(custom_sorted, original, sizeof(original));

    qsort(system_sorted, SIZE, sizeof(Item), unstable_compare);
    my_qsort(custom_sorted, 0, SIZE - 1);

    print_items("Початковий масив:", original, SIZE);
    print_items("Після системної qsort():", system_sorted, SIZE);
    print_items("Після власної my_qsort():", custom_sorted, SIZE);

    printf("\nПеревірка системної qsort(): %s\n",
           is_sorted(system_sorted, SIZE) ? "OK" : "ERROR");

    printf("Перевірка власної my_qsort(): %s\n",
           is_sorted(custom_sorted, SIZE) ? "OK" : "ERROR");

    if (arrays_equal(system_sorted, custom_sorted, SIZE)) {
        printf("Результати системної qsort() і власної my_qsort() однакові.\n");
    } else {
        printf("Результати системної qsort() і власної my_qsort() відрізняються.\n");
    }

    printf("\nПояснення: порівняння є нестабільним для об'єктів з однаковими ключами,\n");
    printf("тому різні реалізації швидкого сортування можуть по-різному переставляти такі елементи.\n");

    return 0;
}
