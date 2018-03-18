#include <iostream>
#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 8

int main() {
    
    omp_set_dynamic(0); // not change number of threads when running
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        printf("Hello, I'm thread number %d of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);
        
    }

    return 0;
}
