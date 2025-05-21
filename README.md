````bash
# README.md for Merge Sort Project
# ------------------------------

## 1. Clone the repository

```bash
# clone and enter project directory
git clone https://github.com/yourusername/project1.git
cd project1
````

## 2. Edit input parameters

Open the source files in `src/` and adjust at the top:

```cpp
#define SIZE 100        // array size
#define PNUM 8          // number of threads (parallel.cpp only)
```

Save your changes.

## 3. Compile the code

```bash
mkdir -p bin

# Sequential version
g++ -O2 -std=c++11 src/sequential.cpp -o bin/sequential

# Parallel version (requires pthreads)
g++ -O2 -std=c++11 src/parallel.cpp -pthread -o bin/parallel
```

## 4. Run the executables

```bash
# Single-threaded test
./bin/sequential

# Multi-threaded test
./bin/parallel
```

## 5. Push changes to GitHub

After editing or adding files:

```bash
git add README.md
git commit -m "Update README instructions"
git push origin main
```

```
```
