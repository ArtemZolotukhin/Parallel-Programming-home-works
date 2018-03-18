#include <stdio.h>
#include <omp.h>
#include <cstdlib>
#include <ctime>

#define ROWS 4
#define COLUMNS 5
#define THREADS 4

#define TIME_TEST_ROWS 8000
#define TIME_TEST_COLUMNS 10000


int* multiplyMatrixByVector(int**, int*, int, int, bool);
int** create2DArray(int, int);
void fillRandom2DArray(int**, int, int, int);
void fillRandomArray(int*, int, int);

int main() 
{
    int **matrix = create2DArray(ROWS, COLUMNS);
    fillRandom2DArray(matrix, ROWS, COLUMNS, 10);
    
    int * vector = new int[COLUMNS];
    fillRandomArray(vector, COLUMNS, 10);
    
    //write it
    printf("<<<DEMONSTRATION>>>\n:Matrix:\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("Vector:\n");
    for (int i = 0; i < COLUMNS; i++) {
        printf("%d ", vector[i]);
    }
    
    int* result = multiplyMatrixByVector(matrix, vector, ROWS, COLUMNS, true);
    printf("\nResult:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("%d ", result[i]);
    }
    //TIME TEST
    printf("\n\n<<<TIME TEST>>>\n");
    double ompTime = 0;
    double antiOmpTime = 0;
    
    int ** bigMatrix = create2DArray(TIME_TEST_ROWS, TIME_TEST_COLUMNS);
    fillRandom2DArray(bigMatrix, TIME_TEST_ROWS, TIME_TEST_COLUMNS, 10);
    
    int * bigVector = new int[TIME_TEST_COLUMNS];
    fillRandomArray(bigVector, TIME_TEST_COLUMNS, 10);
    
    ompTime = omp_get_wtime();
    multiplyMatrixByVector(bigMatrix, bigVector, TIME_TEST_ROWS, TIME_TEST_COLUMNS, true);
    ompTime = omp_get_wtime() - ompTime;
    
    antiOmpTime = clock();
    multiplyMatrixByVector(bigMatrix, bigVector, TIME_TEST_ROWS, TIME_TEST_COLUMNS, false);
    antiOmpTime = (clock() - antiOmpTime) / CLOCKS_PER_SEC;
    
    printf("PARALLEL TIME: %f\n", ompTime);
    printf("NOT PARALLEL TIME: %f\n", antiOmpTime);
    
}

/**
 * size of "vector[]" must be the same as "columns"
*/
int* multiplyMatrixByVector(int ** matrix, int * vector, int rows, int columns, bool isParallel)
{
    int *a = new int[rows];
    for (int i = 0; i < rows; i++) {
        a[i] = 0;
    }
    
    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);
    
    #pragma omp parallel for if (isParallel)
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            a[i] += matrix[i][j] * vector[j];
        }
        //printf("THREAD:%d\n", omp_get_thread_num());
    }

    return a;
}

int ** create2DArray(int rows, int columns) {gege
    int **matrix = new int*[rows];
    for (int i = 0; i < rows; i++) {
        matrix[i] = new int[columns];
    }
    return matrix;
}

void fillRandom2DArray(int ** array, int rows, int columns, int max) {
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            array[i][j] = rand() % max;
        }
    }
    
}

void fillRandomArray(int * array, int size, int max) {
    
    for (int i = 0; i < size; i++) {
        array[i] = rand() % max;
    }
    
}



