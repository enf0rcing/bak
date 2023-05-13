#include <stdio.h>
#include <windows.h>
#include "MySort.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n; i += 1) {
        int flag = 1;
        for (int j = n - 1; j > i; j -= 1) {
            if (arr[j - 1] > arr[j]) {
                flag = 0;
                swap(&arr[j - 1], &arr[j]);
            }
        }
        if (flag) {
            break;
        }
    }
}

void insert_sort(int *arr, int n) {
    for (int i = 1; i < n; i += 1) {
        int tmp = arr[i];
        int j;
        for (j = i; j > 0 && arr[j - 1] > tmp; j -= 1) {
            arr[j] = arr[j -  1];
        }
        arr[j] = tmp;
    }
}

long long sort_test(void (*sort)(int *, int), int *arr, int n) {
    LARGE_INTEGER tmp;
    long long start, end;

    QueryPerformanceCounter(&tmp);
    start = tmp.QuadPart;
    sort(arr, n);
    QueryPerformanceCounter(&tmp);
    end = tmp.QuadPart;

    for (int i = 0; i < n; i += 1) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return end - start;
}

int main() {
    int target[1000] = {0}, test[1000] = {0};

    FILE *fp = fopen(".\\data.txt", "r");

    printf("Input: ");
    int i = 0;
    while (fscanf(fp, "%d", &target[i]) != EOF) {
        printf("%d ", target[i]);
        i += 1;
    }
    printf("\n\n");

    memcpy(test, target, i * sizeof(int));
    long long time = sort_test(bubble_sort, test, i);
    printf("Bubble Sort: %lld\n", time);
    printf("\n");

    memcpy(test, target, i * sizeof(int));
    time = sort_test(insert_sort, test, i);
    printf("Insert Sort: %lld\n", time);
    printf("\n");

    memcpy(test, target, i * sizeof(int));
    time = sort_test(shell_sort, test, i);
    printf("Shell Sort: %lld\n", time);
    printf("\n");

    memcpy(test, target, i * sizeof(int));
    time = sort_test(heap_sort, test, i);
    printf("Heap Sort: %lld\n", time);
    printf("\n");

    memcpy(test, target, i * sizeof(int));
    time = sort_test(merge_sort, test, i);
    printf("Merge Sort: %lld\n", time);
    printf("\n");

    memcpy(test, target, i * sizeof(int));
    time = sort_test(quick_sort, test, i);
    printf("Quick Sort: %lld\n", time);
    printf("\n");

    return 0;
}