#include "MySort.h"

int mergeArr[1000];

void merge(int *arr, int lPos, int lEnd, int rEnd) {
    int rPos = lEnd + 1, tmpPos = lPos, n = rEnd - lPos + 1;
    while (lPos <= lEnd && rPos <= rEnd) {
        if (arr[lPos] <= arr[rPos]) {
            mergeArr[tmpPos++] = arr[lPos++];
        } else {
            mergeArr[tmpPos++] = arr[rPos++];
        }
    }
    while (lPos <= lEnd) {
        mergeArr[tmpPos++] = arr[lPos++];
    }
    while (rPos <= rEnd) {
        mergeArr[tmpPos++] = arr[rPos++];
    }
    for (int i = 0; i < n; i += 1) {
        arr[rEnd] = mergeArr[rEnd];
        rEnd -= 1;
    }
}

void m_sort(int *arr, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        m_sort(arr, left, center);
        m_sort(arr, center + 1, right);
        merge(arr, left, center, right);
    }
}

void merge_sort(int *arr, int n) {
    m_sort(arr, 0, n - 1);
}