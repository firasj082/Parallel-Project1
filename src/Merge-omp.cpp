#include <iostream>
#include <stdio.h>
#include <vector>
#include <omp.h>              // OpenMP header

#define SIZE 1000000
#define PNUM 8

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    // back to stack VLAs for zero-overhead
    int L[n1], R[n2];

    for(int i = 0; i < n1; ++i)      L[i] = arr[l + i];
    for(int j = 0; j < n2; ++j)      R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while(i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];

    while(i < n1) arr[k++] = L[i++];
    while(j < n2) arr[k++] = R[j++];
}

void merge_sort(int arr[], int l, int r) {
    if(l < r) {
        int m = (l + r) >> 1;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void check_sort(int arr[]) {
    for(int i = 0; i < SIZE - 1; ++i) {
        if(arr[i] > arr[i + 1]) {
            puts("Array is not sorted");
            return;
        }
    }
    puts("Array is sorted");
}

int main() {
    double time[5];
    omp_set_num_threads(PNUM);

    for(int iter = 0; iter < 5; ++iter) {
        static int arr[SIZE];         // stack allocation, too
        // fill outside timing
        for(int i = 0; i < SIZE; ++i)
            arr[i] = rand() % 10001;

        int chunk = SIZE / PNUM;
        int rem   = SIZE % PNUM;

        double start = omp_get_wtime();

        // parallel chunked sort
        #pragma omp parallel for schedule(static)
        for(int t = 0; t < PNUM; ++t) {
            int left  = t*chunk + (t < rem ? t : rem);
            int len   = chunk + (t < rem ? 1 : 0);
            int right = left + len - 1;
            merge_sort(arr, left, right);
        }

        // collect runs
        std::vector<std::pair<int,int>> runs;
        runs.reserve(PNUM);
        {
            int left = 0;
            for(int t = 0; t < PNUM; ++t) {
                int len   = chunk + (t < rem ? 1 : 0);
                runs.emplace_back(left, left + len - 1);
                left += len;
            }
        }

        // sequential iterative merging
        while(runs.size() > 1) {
            std::vector<std::pair<int,int>> next;
            next.reserve((runs.size()+1)/2);
            for(size_t i = 0; i+1 < runs.size(); i += 2) {
                auto [L, M] = runs[i];
                auto [_, R] = runs[i+1];
                merge(arr, L, M, R);
                next.emplace_back(L, R);
            }
            if(runs.size() & 1) 
                next.push_back(runs.back());
            runs.swap(next);
        }

        double end = omp_get_wtime();
        check_sort(arr);

        time[iter] = end - start;
        printf("Iteration %d time: %f s\n", iter+1, time[iter]);
    }

    double avg = (time[0]+time[1]+time[2]+time[3]+time[4]) / 5.0;
    printf("Average time: %f s\n", avg);
    return 0;
}
