#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;


int main() {

    int a, b;
    a = 5;
    b = 5;

    cout << "Before first parallel block: a = " << a << "; b = " << b << endl;

    omp_set_num_threads(4);
    #pragma omp parallel private(a) firstprivate(b)
    {
        unsigned int thread_num = omp_get_thread_num();

        /* Sleep for right output without collision.
         * Now the parallel has lost all meaning, but our target learn how work "private",
         * "firstprivate" and may be other things with variables in this
         * example
        **/
        usleep(100 * thread_num);

        a += omp_get_num_threads();
        b += omp_get_num_threads();
        cout << "Inside first parallel block at " << thread_num << " thread: a = " << a << "; b = " << b << endl;

    }
    cout << "After first parallel block: a = " << a << "; b = " << b << endl;

    omp_set_num_threads(2);
    #pragma omp parallel shared(a) firstprivate(b)
    {

        unsigned int thread_num = omp_get_thread_num();
        //Sleep again
        usleep(100 * thread_num);

        a -= omp_get_thread_num();
        b -= omp_get_thread_num();

        cout << "Inside second parallel block at " << thread_num << " thread: a = " << a << "; b = " << b << endl;

    }
    cout << "After second parallel block: a = " << a << "; b = " << b << endl;
    return 0;
}
