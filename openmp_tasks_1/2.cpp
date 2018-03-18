#include <stdio.h>
#include <omp.h>


int main() {
    omp_set_dynamic(0); // not change number of threads when running

    int num_threads = 3;
    omp_set_num_threads(num_threads);

    #pragma omp parallel if (num_threads > 1)
    if (num_threads > 1)
    {
        printf("Hello, I'm thread number %d of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);
    }

    num_threads = 1;
    omp_set_num_threads(num_threads);

    #pragma omp parallel if (num_threads > 1)
    if (num_threads > 1)
    {
        printf("ANTIHello, I'm thread number %d of %d\n", omp_get_thread_num(), omp_get_num_threads() - 1);
    }
    return 0;
}

