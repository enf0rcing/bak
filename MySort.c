#include <stdio.h>
#include <string.h>
#include <sys/time.h>
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
            arr[j] = arr[j - 1];
        }
        arr[j] = tmp;
    }
}

long sort_test(void (*sort)(int *, int), int *arr, int n) {
    struct timeval tmp;
    long start, end;

    gettimeofday(&tmp, 0);
    start = tmp.tv_usec;
    sort(arr, n);
    gettimeofday(&tmp, 0);
    end = tmp.tv_usec;

    return end - start;
}

int main() {
    int n, target[1000] = {0}, test[1000] = {0};
    long time;
    char sort_name_arr[6][15] = {"bubble_sort", "insert_sort", "shell_sort", "heap_sort", "merge_sort", "quick_sort"};
    void (*sort_fun_arr[6])(int *, int) = {bubble_sort, insert_sort, shell_sort, heap_sort, merge_sort, quick_sort};
    FILE *fp = fopen("data.txt", "r");

    if (fp) {
        n = 0;
        printf("Input: ");
        while (fscanf(fp, "%d", &target[n]) != EOF) {
            printf("%d ", target[n]);
            n += 1;
        }
        fclose(fp);
        printf("\n");

        for (int i = 0; i < 6; i += 1) {
            memcpy(test, target, n * sizeof(int));
            time = sort_test(sort_fun_arr[i], test, n);
            printf("\n%s: %ld (ms)", sort_name_arr[i], time);
        }
    } else {
        printf("Can not open data.txt");
    }

    return 0;
}