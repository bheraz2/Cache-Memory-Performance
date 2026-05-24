/*
Name: Bryan Heraz
Date: 5/6/2025
COMPE 271
Description: The purpose of this program is to demonstrate the use of cache memory in C.
2 test cases are provided to show the difference in chache performance. A simpler vector addition algorithm is used to
demonstrate performnace of cache.
*/
#define _POSIX_C_SOURCE 200809L // access clock_gettime()
#define OP 100000000 // number of operations for stride case
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

// declaring fucntion
void array(int *arr, int size);
void contiguouse_access(int *A, int *B, int *C, int size);
void strided_access(int *A, int *B, int *C, int size, int stride);
static uint64_t get_time(void);

// get_time() function that returns time into nanoseconds for cache performance testing
static uint64_t get_time(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts); // time coversion to nanoseconds
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

// array() fucntion that creates an array of numbers based on size provided in main fucntion.
void array(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        arr[i] = i;
    }
}

// contiguouse_access() function, itirates throuhg the whole array and sums vector . Size of array will be tested in main fucntion
void contiguouse_access(int *A, int *B, int *C, int size)
{
    for (int i = 0; i < size; i++)
    {
        C[i] = A[i] + B[i]; 
    }
}

// strided_access() function, jumps throught the array base on slected stride
void strided_access(int *A, int *B, int *C, int size, int stride)
{
    int index = 0;
    for (int i = 0; i < OP; i++)
    {
        C[index] = A[index] + B[index];  
        index = (index + stride) % size; // control pattern
    }
}

// Testing cases for cahce performance
int main(void)
{
    int number_size = 6;
    int number_stride = 8;
    int sizes[] = {1000,
                   10000,
                   100000,
                   1000000,
                   10000000,
                   100000000};

    int strides[] = {1, 2, 4, 8, 16, 32, 64, 128};

    // Case 1: Contiguous Acces with difrrent array sizes
    printf("------------------------------------------------------\n");
    printf("Contiguous Access Performance (small to large array)\n");
    printf("%-15s %-20s\n", "Array Size", "Time (ms)");
    printf("-------------------------------------------------------\n");

    // Loop throuhg array of sizes, tested each size and prints time taken to perfom sum for each size of array
    for (int i = 0; i < number_size; i++)
    {
        int current_size = sizes[i]; // creating arrayof current size

        int *A = malloc(current_size * sizeof(int)); // allocating memory for array
        int *B = malloc(current_size * sizeof(int)); // allocating memory for array
        int *C = malloc(current_size * sizeof(int)); // allocating memory for array

        array(A, current_size); // creating array
        array(B, current_size); // creating array

        uint64_t time_started = get_time();        // start time recorded
        contiguouse_access(A, B, C, current_size); // contiguouse funtion called to text performance
        uint64_t time_ended = get_time();          // end time recorded

        printf("%-10d %20.3f\n", current_size, (double)(time_ended - time_started) / 1e6); // prints total time take to perform addition of array when acccessed contiguously
        free(A);    
        free(B);
        free(C);                                                                      
    }

    printf("\n\n");

    // Case 2: Strided Access with fixed size(demnostrattng chache misses)
    printf("------------------------------------------------------\n");
    printf("Strided Acces performnace (fixed size,  different strides)\n");
    printf("%-15s %-20s\n", "Stride", "Time (ms)");
    printf("-------------------------------------------------------\n");

    int fixed_size = 32000000;                 // fixed size of array, above size of L3 cache
    int *A = malloc(fixed_size * sizeof(int)); // allocating memory for array
    int *B = malloc(fixed_size * sizeof(int)); // allocating memory for array
    int *C = malloc(fixed_size * sizeof(int)); // allocating memory for array

    array(A, fixed_size); // create array
    array(B, fixed_size); // create array

    for (int i = 0; i < number_stride; i++)
    {
        int current_stride = strides[i]; // curretn stride in strides array

        uint64_t time_started = get_time();                  // start time recorded
        strided_access(A, B, C, fixed_size, current_stride); 
        uint64_t time_ended = get_time();                    // end time recorded

        printf("%-10d %20.3f\n", current_stride, (double)(time_ended - time_started) / 1e6); // prints total time take to perform addition of elemnts in the array
    }
    free(A); // frees memory
    free(B); // frees memory
    free(C); // frees memory
    return 0;
}