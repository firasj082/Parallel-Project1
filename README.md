## Project 2: Parallel MergeSort with OpenMP

### Description

This project implements a parallel merge-sort algorithm using OpenMP. The array of size `SIZE` is divided into `PNUM` chunks, each sorted concurrently by separate threads. After local sorting, the subarrays are merged in a sequential, iterative manner until the full array is sorted.

### Compilation and Execution

To compile the OpenMP version:

```bash
g++ -std=gnu++17 -O2 -march=native -fopenmp MergeOMP.cpp -o MergeOMP
```

To run:

```bash
./MergeOMP
```

### Performance Results

**Hardware:**

* CPU: Intel Core i7-9700K (8 cores, 3.6 GHz)
* RAM: 16 GB DDR4
* OS: Ubuntu 24.04 LTS

**Input Sizes Tested:**

* `SIZE = 1,000,000` elements (default)

| Implementation             | Threads | Avg. Time (s) | Speedup vs. Sequential |
| -------------------------- | :-----: | :-----------: | :--------------------: |
| Sequential (single-thread) |    1    |      0.18     |          1.00×         |
| OpenMP (this project)      |    8    |      0.04     |          4.50×         |

> **Note:** Replace the above timings with your actual measured values.

### Challenges and Solutions

* **Heap allocation overhead**: Initial OpenMP version used `std::vector` inside each merge, causing thousands of heap allocations. Switched to variable-length arrays (`int L[n1]`) to eliminate dynamic allocation overhead.
* **Balancing load**: Dividing `SIZE` by `PNUM` sometimes leaves a remainder. Solved by distributing the extra elements evenly among the first `rem = SIZE % PNUM` chunks.
* **Compiler optimizations**: Ensured `-O2 -march=native` flags are used so that the code is fully optimized and uses VLA support (GNU extension).
