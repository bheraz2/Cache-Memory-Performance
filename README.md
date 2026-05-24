# Cache Memory Performance

## Overview
This project focuses on analyzing CPU cache performance and memory access behavior using C programming. The main focus is to demonstrate how cache hits, cache misses, and spatial locality affect time performance.

## Project Goal
Modern CPUs use cache memory to access data faster. If data fits inside cache, execution time is fast because cache hits occur. However, if data exceed cache size, the CPU needs to fetch data from main memory which increases execution time.

Tests:
- Different Array Sizes
- Contiguous Memory Access
- Non-Contiguous Memory Access

## Experiments

### Experiment 1: Array Size
Sequential vector addition is performed using different array sizes to analyze how cache size affects execution time.

### Experiment 2: Stride Access
Different stride values are used to test non-contiguous memory access patterns. Large stride values reduce spatial locality and increase cache misses.

## Technologies Used
- C Programming
- malloc()
- clock_gettime()
- POSIX timing functions

## System Specifications
- AMD Ryzen 5 7600X
  - L1 Cache: 384KB
  - L2 Cache: 6MB
  - L3 Cache: 32MB

## Results
- Small arrays execute faster because data fit inside cache.
- Larger arrays increase execution time due to cache misses.
- Large stride values waste cache lines and reduce performance.

## How to Run

```bash
gcc cache.c -o cache
./cache
```
