#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits>

#define RANDOM_TOP 100
#define ROWS 6
#define COLUMNS 8
#define THREADS 4

using namespace std;

int main() {

    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);

    int d[ROWS][COLUMNS];

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            d[i][j] = rand() % RANDOM_TOP;
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }


    int max = numeric_limits<int>::min();
    int min = numeric_limits<int>::max();

    #pragma omp parallel for
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {

            if (d[i][j] > max) {
                #pragma omp critical
                {
                    max = d[i][j];
                }
            }
            if (d[i][j] < min) {
                #pragma omp critical
                {
                    min = d[i][j];
                }
            }
        }
    }
    printf("MIN: %d; MAX: %d\n", min, max);

}
