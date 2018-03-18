#include <iostream>
#include <omp.h>
#include <math.h>
#include <stdio.h>

#define NUM_THREADS 8
#define BIN_LENGTH 30

using namespace std;

int main() {
    
    omp_set_dynamic(0); // not change number of threads when running
    omp_set_num_threads(NUM_THREADS);
    
    //756893125 in decimal
    int a[BIN_LENGTH] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    
    int result = 0;

    #pragma omp parallel for reduction(+:result)
    for (int i = 0; i < BIN_LENGTH; i++) {
        if (a[i] == 1) {
            result += pow(2, BIN_LENGTH - i - 1);
        }
    }

    printf("%d\n", result);

    return 0;
}
