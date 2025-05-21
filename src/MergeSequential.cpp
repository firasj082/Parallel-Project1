#include <iostream>
#include <stdio.h>
#include <chrono>

#define SIZE 1000000

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (i = 0; i < n1; i++) L[i] = arr[l + i];
    for (j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    i = 0; j = 0; k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void merge_sort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void check_sort(int arr[]) {
    for (int i = 0; i < SIZE - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            printf("Array is not sorted\n");
            return;
        }
    }
    printf("Array is sorted\n");
}


int main() {
    float time[5];
    for(int i=0; i<5; i++){
    int arr[SIZE];

    for(int i=0; i < SIZE; i++) {
        arr[i] = rand() % 10001;
    }

    auto start = std::chrono::high_resolution_clock::now();
    merge_sort(arr, 0, SIZE - 1);
    auto end = std::chrono::high_resolution_clock::now();
    check_sort(arr);
    printf("\nTime taken: %f seconds\n", std::chrono::duration<double>(end - start).count());
    time[i] = std::chrono::duration<double>(end - start).count();
}
    float avg = (time[0] + time[1] + time[2] + time[3] + time[4]) / 5.0;
    printf("\nAverage time taken: %f seconds\n", avg);
    return 0;
}
