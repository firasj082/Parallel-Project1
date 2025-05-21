#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <chrono>
#include <vector>

#define SIZE 1000000
#define PNUM 8

struct ThreadData {
    int *arr;
    int l;
    int r;
};

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

void* thread_merge_sort(void* args) {
    ThreadData *data = (ThreadData*)args;
    merge_sort(data->arr, data->l, data->r);
    return NULL;
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
    for(int i = 0; i < 5 ; i++){
    int arr[SIZE];
   
    for(int i=0; i < SIZE; i++) {
        arr[i] = rand() % 10001;
    }

    auto start = std::chrono::high_resolution_clock::now();
    pthread_t threads[PNUM];
    ThreadData thread_data[PNUM];
    int left = 0;
    int chunk = SIZE / PNUM;
    int rem = SIZE % PNUM;
    for(int i = 0; i < PNUM; i++) {
        thread_data[i].arr = arr;
        thread_data[i].l = left;
        thread_data[i].r = left + chunk + (i < rem) - 1;
        pthread_create(&threads[i], NULL, thread_merge_sort, (void*)&thread_data[i]);
        left = thread_data[i].r + 1;
    }

    for (int i = 0; i < PNUM; i++) {
        pthread_join(threads[i], NULL);
    }
    
     std::vector<std::pair<int,int>> runs;
    runs.reserve(PNUM);
    for (int i = 0; i < PNUM; i++) {
        runs.emplace_back(thread_data[i].l,thread_data[i].r);
    }
    
    while (runs.size() > 1) {
        std::vector<std::pair<int,int>> next;
        next.reserve((runs.size()+1)/2);

        for (size_t i = 0; i + 1 < runs.size(); i += 2) {
            int left  = runs[i].first;
            int mid   = runs[i].second;
            int right = runs[i+1].second;
            merge(arr, left, mid, right);
            next.emplace_back(left, right);
        }
        if (runs.size() % 2 == 1) {
            next.push_back(runs.back());
        }
        runs.swap(next);
    }

    auto end = std::chrono::high_resolution_clock::now();

    check_sort(arr);
    time[i] = (std::chrono::duration<double>(end - start).count());
    printf("\nTime taken: %f seconds\n", std::chrono::duration<double>(end - start).count());
}
    float avg = (time[0]+time[1]+time[2]+time[3]+time[4])/5.0;
    printf("\nAverage time taken: %f seconds\n", avg);
    return 0;
}