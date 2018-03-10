#include <iostream>
#include <omp.h>

using namespace std;
int main() {
    omp_set_dynamic(0); // not change number of threads when running

    int num_threads = 3;
    omp_set_num_threads(num_threads);

    #pragma omp parallel if (num_threads > 1)
    if (num_threads > 1)
    {
        cout << "Hello, I'm thread number " <<
        omp_get_thread_num() << " of " << omp_get_num_threads() << endl;
    }

    num_threads = 1;
    omp_set_num_threads(num_threads);

    #pragma omp parallel if (num_threads > 1)
    if (num_threads > 1)
    {
        cout << "Hello, I'm  thread number " <<
        omp_get_thread_num() << " of " << omp_get_num_threads() <<  ", BUT I AM DEAD!" << endl;
    }
    return 0;
}

