#include "MySort.h"

#define CUTOFF 15

int median3(int *arr, int left, int right) {
    int center = (left + right) / 2;
    if (arr[left] > arr[center]) {
        swap(&arr[left], &arr[center]);
    }
    if (arr[left] > arr[right]) {
        swap(&arr[left], &arr[right]);
    }
    if (arr[center] > arr[right]) {
        swap(&arr[center], &arr[right]);
    }
    swap(&arr[center], &arr[right - 1]);
    return arr[right - 1];
}

void q_sort(int *arr, int left, int right) {
    if (right - left >= CUTOFF) {
        int pivot = median3(arr, left, right);
        int l = left, r = right - 1;
        while (1) {
            do {
                l += 1;
            } while (arr[l] < pivot);
            do {
                r -= 1;
            } while (arr[r] > pivot);
            if (l < r) {
                swap(&arr[l], &arr[r]);
            } else {
                break;
            }
        }
        swap(&arr[l], &arr[right - 1]);
        q_sort(arr, left, l - 1);
        q_sort(arr, l + 1, right);
    } else {
        insert_sort(&arr[left], right - left + 1);
    }
}

void quick_sort(int *arr, int n) {
    q_sort(arr, 0, n - 1);
}