#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

#define N 6
#define M 8
#define NUM_THREADS 4

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

    #pragma omp sections
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
            cout << "Hello, I'm thread number " << omp_get_thread_num() << endl
            << "Average = " << average << endl;


        }
        #pragma omp section
        {
            int max = INT8_MIN;
            int min = INT8_MAX;
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
            cout << "Hello, I'm thread number " << omp_get_thread_num() << endl
            << "Min = " << min << "; Max = " << max << endl;
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
            cout << "Hello, I'm thread number " << omp_get_thread_num() << endl
            << "Multiple three count = " << multiple_three_count << endl;
        }
    }

    return 0;
}
