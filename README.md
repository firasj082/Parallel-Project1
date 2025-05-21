# Merge Sort Comparison

This repository contains two implementations of Merge Sort in C/C++ (or your language of choice):

* **Sequential Merge Sort**
* **Parallel Merge Sort** (multi-threaded)

Both implementations include a built-in validation function (`check_sort`) and a loop for computing average runtimes over multiple runs.

---

## Contents

* [`sequential/`](#sequential)
* [`parallel/`](#parallel)
* [Validation (`check_sort`)](#validation)
  
---

## Sequential Merge Sort

### Configuration

* **`SIZE`**: The number of elements to sort.
  Defined at the top of `sequential/main.c` (or `.cpp`).

```c
#define SIZE 1000000  // change this value to adjust input size
```

### Build & Run

```bash
cd sequential
make                # or your build command
i./sequential       # runs the sequential merge sort
```

The program will:

1. Generate an array of `SIZE` random numbers.
2. Sort it using the sequential merge sort.
3. Call `check_sort` to validate the result.
4. Print the elapsed time.
5. Repeat `NUM_TRIALS` times (default in code) and print the average.

---

## Parallel Merge Sort

### Configuration

* **`SIZE`**: Number of elements to sort (same as sequential).
* **`PNUM`**: Number of threads/processors to use.

Defined at the top of `parallel/main.c`:

```c
#define SIZE 1000000  // input size
#define PNUM 4        // number of threads
```

### Build & Run

```bash
cd parallel
make                # or your build command
i./parallel         # runs the parallel merge sort
```

This program will:

1. Generate an array of `SIZE` random numbers.
2. Spawn `PNUM` worker threads, each sorting a sub-array.
3. Merge the sorted sub-arrays.
4. Validate with `check_sort`.
5. Measure and print runtime and average over `NUM_TRIALS` runs.

---

## Validation (`check_sort`)

Each implementation includes a function named `check_sort(arr, size)` that:

1. Verifies the array is sorted in non-decreasing order.
2. Prints a sorted or not sorted message.

> You do **not** need to run any extra commands—validation runs automatically after each sort.

---
