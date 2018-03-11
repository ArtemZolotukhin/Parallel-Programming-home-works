#include <iostream>
#include <omp.h>

using namespace std;

#define N 10
#define NUM_THREADS 4

int main() {

    omp_set_dynamic(0);
    omp_set_num_threads(NUM_THREADS);

    int a[N];
    int b[N];

    for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i * 2;
    }

    int average_a = 0;
    int average_b = 0;

    #pragma omp parallel for reduction(+:average_a, average_b)
    for (int i = 0; i < N; i++) {
        average_a += a[i];
        average_b += b[i];
    }

    average_a /= N;
    average_b /= N;

    cout << "Average a = " << average_a << "; Average b = " << average_b << endl;

    return 0;
}
