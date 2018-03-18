#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <stdio.h>

using namespace std;

#define N 12

int main() {

    int a[N];
    int b[N];
    int c[N];

    omp_set_dynamic(0);
    omp_set_num_threads(3);
    
    #pragma omp parallel for schedule(static, 4)
    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
        printf("blocck = 1, thread = %d, thread_count = %d, a[%d] = %d, b[%d] = %d\n", 
            omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i]);
    }

    omp_set_num_threads(3);
    #pragma omp parallel for schedule(dynamic, 3)
    for (int i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
        printf("blocck = 2, thread = %d, thread_count = %d, c[%d] = %d\n", 
            omp_get_thread_num(), omp_get_num_threads(), i, c[i]);
    }

    return 0;
}
