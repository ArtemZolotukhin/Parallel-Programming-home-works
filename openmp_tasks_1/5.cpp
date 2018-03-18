#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <stdio.h>
#include <limits>

using namespace std;

#define N 6
#define M 8
#define NUM_THREADS 3

int main() {

    omp_set_dynamic(0);
    omp_set_num_threads(NUM_THREADS);

    int d[N][M];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            d[i][j] = rand() % 100;
            cout << d[i][j] << " ";
        }
        cout << endl;
    }
    
    
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            int average = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    average += d[i][j];
                }
            }
            average /= N * M;
            printf("Hello, I'm thread number %d. Average = %d\n", omp_get_thread_num(), average);


        }
        #pragma omp section
        {
            int max = numeric_limits<int>::min();
            int min = numeric_limits<int>::max();
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (d[i][j] > max) {
                        max = d[i][j];
                    }
                    if (d[i][j] < min) {
                        min = d[i][j];
                    }
                }
            }
            printf("Hello, I'm thread number %d; Min = %d; Max = %d\n", omp_get_thread_num(), min, max);
            
        }
        #pragma omp section
        {
            int multiple_three_count = 0;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < M; j++) {
                    if (d[i][j] % 3 == 0) {
                        multiple_three_count++;
                    }
                }
            }
            printf("Hello, I'm thread number %d;\n; Multiple three count = %d\n", omp_get_thread_num(), multiple_three_count);
            
        }
    }

    return 0;
}
