//
// Created by n3ki4 on 4/1/22.
//
#include <stdlib.h>
#include <stdio.h>
#define SIZE 10


void bubble_sort(int *arr) {
    int tmp;
    for (int i = 0; i < SIZE - 1; ++i) {
        for (int j = 0; j < SIZE - 1 - i; ++j) {
            if (arr[j] > arr[j + 1]) {
                tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}



int main() {
    int *arr = calloc(SIZE, sizeof (int));
    for (int i = 0; i < SIZE; ++i) {
        arr[i] = SIZE - i;
    }

    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }

    bubble_sort(arr);

    putchar('\n');
    for (int i = 0; i < SIZE; ++i) {
        printf("%d ", arr[i]);
    }

    free(arr);

}