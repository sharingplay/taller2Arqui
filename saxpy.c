#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define N 10000000 //size of the vectors

/*SAXPY: single precision A*X + Y
this takes 2 vectors (X,Y) of N elements and an scalar
then we muliply the X vector with A and add it to Y*/


int main() {
    float a = 4.0;
    float *x = (float*) malloc(N * sizeof(float));
    float *y = (float*) malloc(N * sizeof(float));
    double start_time_serial, run_time_serial, start_time_parallel, run_time_parallel;
    srand(time(NULL)); //seed for the random numbers

    // store random values from 1 to 100 on the arrays
    for (int i = 0; i < N; i++) {
        x[i] = (rand() % 100) + 1;
        y[i] = (rand() % 100) + 1;
    }

    // Serial SAXPY calculation
    start_time_serial = omp_get_wtime(); // get starting loop time

    for (int i = 0; i < N; i++) {
        y[i] = a * x[i] + y[i];
    }

    run_time_serial = omp_get_wtime() - start_time_serial; // time spent in the for loop

    printf("Vector Size: %d , Serial run time: %f seconds\n", N, run_time_serial);

    // Prallel SAXPY calculation
    start_time_parallel = omp_get_wtime();

    #pragma omp parallel for // indicate parallelization of the for loop
    for (int i = 0; i < N; i++) {
        y[i] = a * x[i] + y[i];
    }
      
    run_time_parallel = omp_get_wtime() - start_time_parallel; // time spent in the for loop with parallelism
    printf("Vector Size: %d , Parallel run time: %f seconds\n", N, run_time_parallel);

    return 0;
}