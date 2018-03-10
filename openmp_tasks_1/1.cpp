#include <iostream>
#include <omp.h>

using namespace std;

#define NUM_THREADS 8

int main() {
    
    omp_set_dynamic(0); // not change number of threads when running
    omp_set_num_threads(NUM_THREADS);

    #pragma omp parallel
    {
        cout << "Hello, I'm thread number " <<
        omp_get_thread_num() << " of " << omp_get_num_threads() << endl;
        
    }

    return 0;
}
