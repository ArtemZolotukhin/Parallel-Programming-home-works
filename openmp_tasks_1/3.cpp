#include <iostream>
#include <omp.h>
#include <stdio.h>

using namespace std;


int main() {

    int a, b;
    a = 5;
    b = 5;

    printf("Before first parallel block: a = %d; b = %d\n", a, b);

    omp_set_num_threads(4);
    #pragma omp parallel private(a) firstprivate(b)
    {
        int thread_num = omp_get_thread_num();

        a += omp_get_thread_num();
        b += omp_get_thread_num();
        
        printf("Inside first parallel block at %d thread: a = %d; b = %d\n", thread_num, a, b);

    }
    printf("After first parallel block: a = %d; b = %d\n", a, b);

    omp_set_num_threads(2);
    #pragma omp parallel shared(a) private(b)
    {

        int thread_num = omp_get_thread_num();

        a -= omp_get_thread_num();
        b -= omp_get_thread_num();

        printf("Inside second parallel block at %d thread: a = %d; b = %d\n", thread_num, a, b);

    }
    printf("After second parallel block: a = %d; b = %d\n", a, b);
    return 0;
}
