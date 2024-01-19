#include "solutions.h"
#include <stdlib.h>

int running_total(int x) {
    static int sum = 0;
    sum += x;
    return sum;
}

int* reverse(int* arr, int len) {
    int* rev_arr = (int*)calloc(len, sizeof(int));
    if (rev_arr == NULL) {
        return NULL;  // calloc failed
    }

    for (int i = 0; i < len; i++) {
        rev_arr[i] = arr[len - 1 - i];
    }

    return rev_arr;
}

void reverse_in_place(int* arr, int len) {
    int temp;
    for (int i = 0; i < len / 2; i++) {
        temp = arr[i];
        arr[i] = arr[len - 1 - i];
        arr[len - 1 - i] = temp;
    }
}

int num_occurrences(int* arr, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == value) {
            count++;
        }
    }
    return count;
}