## Project 2: Parallel MergeSort with OpenMP

### Description

This project implements a parallel merge-sort algorithm using OpenMP. The array of size `SIZE` is divided into `PNUM` chunks, each sorted concurrently by separate threads. After local sorting, the subarrays are merged in a sequential, iterative manner until the full array is sorted.

### Configuration

#define SIZE 1000000  // change this value to adjust input size
```
* **`SIZE`**: Number of elements to sort (same as sequential).
* **`PNUM`**: Number of threads/processors to use.

Defined at the top of `parallel/main.c`:

```c
#define SIZE 1000000  // input size
#define PNUM 4        // number of threads
```


### Performance Results

**Hardware:**

* CPU: Intel Core i5-9300H (8 cores, 2.4 GHz)
* RAM: 16 GB DDR4
* OS: Ubuntu 24.04 LTS

**Input Sizes Tested:**

* `SIZE = 1,000,000` elements 

| Implementation       | Threads | Avg. Time (s) | Speedup vs. Sequential |
| -------------------- | :-----: | :-----------: | :--------------------: |
| Sequential           |    1    |      0.16     |          1.00×         |
| OpenMP               |    8    |      0.04     |          4.00×         |
| OpenMP               |    4    |      0.06     |          2.67×         |
| OpenMP               |    2    |      0.092    |          1.74×         |

* `SIZE = 10,000` elements

| Implementation       | Threads | Avg. Time (s) | Speedup vs. Sequential |
| -------------------- | :-----: | :-----------: | :--------------------: |
| Sequential           |    1    |      0.0013   |          1.00×         |
| OpenMP               |    8    |      0.00069  |          1.88×         |
| OpenMP               |    4    |      0.00063  |          2.06×         |
| OpenMP               |    2    |      0.0007   |          1.85×         |

* `SIZE = 100` elements

| Implementation       | Threads | Avg. Time (s) | Speedup vs. Sequential |
| -------------------- | :-----: | :-----------: | :--------------------: |
| Sequential           |    1    |      0.000008 |          1.00×         |
| OpenMP               |    8    |      0.00032  |          0.025×         |
| OpenMP               |    4    |      0.000044 |          0.18×         |
| OpenMP               |    2    |      0.000032 |          0.25×         |


### Challenges and Solutions

* **Heap allocation overhead**: Initial OpenMP version used `std::vector` inside each merge, causing thousands of heap allocations. Switched to variable-length arrays (`int L[n1]`) to eliminate dynamic allocation overhead.
* **Balancing load**: Dividing `SIZE` by `PNUM` sometimes leaves a remainder. Solved by distributing the extra elements evenly among the first `rem = SIZE % PNUM` chunks.

Note: The times compared to the pthread are way better due to the implementation in the pthread version I made the code by myself where it had many unnecessary complications in the omp I didn't have to deal with the same issues due to omp nature which resulted in better timing for smaller array inputs.
