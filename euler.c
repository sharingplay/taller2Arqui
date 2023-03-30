#include <stdio.h>
#include <math.h>
#include <omp.h>

// serial euler calculation
double serial_euler(int n) {
    double e = 1.0;
    double fact = 1.0;
    for (int i = 1; i <= n; i++) {
        fact *= i;
        e += 1.0 / fact;
    }
    return e;
}

// parallel euler calculation
double parallel_euler(int n) {
    double e = 1.0;
    double fact = 1.0;
    #pragma omp parallel for reduction(*:fact) reduction(+:e) // accumulative sum and multiplication
    for (int i = 1; i <= n; i++) {
        fact *= i;
        e += 1.0 / fact;
    }
    return e;
}

int main() {
    int n = 100000000;
    double start_time_serial, start_time_parallel, run_time_serial, run_time_parallel, euler_serial, euler_parallel;

    // Serial time meassure
    start_time_serial = omp_get_wtime();
    euler_serial = serial_euler(n);
    run_time_serial = omp_get_wtime() - start_time_serial;

    printf("Serial Euler value with %d iterations: %lf , run time: %lf seconds\n", n, euler_serial, run_time_serial);

    // Parallel time meassure
    start_time_parallel = omp_get_wtime();
    euler_parallel = parallel_euler(n);
    run_time_parallel = omp_get_wtime() - start_time_parallel;

    printf("Parallel Euler value with %d iterations: %lf , run time %lf seconds\n", n, euler_parallel, run_time_parallel);

    return 0;
}
