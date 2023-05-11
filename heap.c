#include "MySort.h"

void percolate_down(int *arr, int i, int n) {
    int tmp = arr[i];
    int child;
    for (; 2 * i + 1 < n; i = child) {
        child = 2 * i + 1;
        if (child != n - 1 && arr[child + 1] > arr[child]) {
            child += 1;
        }
        if (tmp < arr[child]) {
            arr[i] = arr[child];
        } else {
            break;
        }
    }
    arr[i] = tmp;
}

void heap_sort(int *arr, int n) {
    for (int i = n / 2; i >= 0; i -= 1) {
        percolate_down(arr, i, n);
    }
    for (int i = n - 1; i > 0; i -= 1) {
        swap(&arr[0], &arr[i]);
        percolate_down(arr, 0, i);
    }
}