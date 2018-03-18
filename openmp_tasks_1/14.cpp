#include <iostream>
#include <omp.h>
#include <stdio.h>

#define NUM_THREADS 4
#define N 210

using namespace std;

int main() {
    
    omp_set_dynamic(0); // not change number of threads when running
    omp_set_num_threads(NUM_THREADS);
    
    int result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < N; i ++) {
        result = result + 2 * i + 1;
    }

    printf("%d\n", result);

    return 0;
}
