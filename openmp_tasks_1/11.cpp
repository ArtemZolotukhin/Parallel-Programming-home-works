#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits>


#define RANDOM_TOP 70
#define THREADS 4
#define DIVIDER 7
#define SIZE 20

using namespace std;

int main() {

    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);

    int a[SIZE];

    for (int i = 0; i < SIZE; i++){
        a[i] = rand() % RANDOM_TOP;
        printf("%d ", a[i]);
    }

    int max = numeric_limits<int>::min();
    
    #pragma omp parallel for shared(max)
    for (int i = 0; i < SIZE; i++) {
        if (a[i] % DIVIDER == 0) {
            #pragma omp critical
            {
                if (a[i] > max) {
                    max = a[i];
                }
            }
        }
    }

    printf("Max %%7 : %d\n", max);
}
