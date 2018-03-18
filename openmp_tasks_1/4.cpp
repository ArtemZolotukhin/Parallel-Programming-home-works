#include <iostream>
#include <omp.h>
#include <limits>

using namespace std;

#define N 10
#define NUM_THREADS 2

int main() {

    omp_set_dynamic(0); // not change number of threads when running
    omp_set_num_threads(NUM_THREADS);

    int a[N];
    int b[N];

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i;
    }

    int min_a = numeric_limits<int>::max();
    int max_b = numeric_limits<int>::min();

    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            for (int i = 0; i < N; i++) {
                if (a[i] < min_a) {
                    min_a = a[i];
                }
            }
        } else {
            for (int i = 0; i < N; i++) {
                if (b[i] > max_b) {
                    max_b = b[i];
                }
            }
        }
    }

    cout << "Min a: " << min_a << endl;
    cout << "Max b: " << max_b << endl;

    return 0;
}
