#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define RANDOM_TOP 90
#define THREADS 4
#define SIZE 30
#define DEVIDER 9

int main() {

    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);

    int a[SIZE];
    int deviderCount = 0;
    
    for (int i = 0; i < SIZE; i++){
        a[i] = rand() % RANDOM_TOP;
        printf("%d ", a[i]);
    }
    
    #pragma omp parallel for shared(deviderCount)
    for (int i = 0; i < SIZE; i++) {
        if (a[i] % DEVIDER == 0) {
            #pragma omp atomic
            deviderCount += 1;
        }
    }
    
    printf("\nCount of %% %d == 0 : %d\n", DEVIDER, deviderCount);
}
