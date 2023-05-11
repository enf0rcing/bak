#include "MySort.h"

const int Hibbard[10] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023};

void shell_sort(int *arr, int n) {
    int index = 0;
    while (Hibbard[index] < n) {
        index += 1;
    }
    for (; index > 0; index -= 1) {
        int increment = Hibbard[index - 1];
        for (int i = increment; i < n; i += 1) {
            int tmp = arr[i];
            int j;
            for (j = i; j >= increment; j -= increment) {
                if (tmp < arr[j - increment]) {
                    arr[j] = arr[j - increment];
                } else {
                    break;
                }
            }
            arr[j] = tmp;
        }
    }
}