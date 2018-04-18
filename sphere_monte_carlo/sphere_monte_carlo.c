#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define DIMENSION_COUNT 20
#define SPHERE_RADIUS 1
#define POINT_COUNT 10000000
#define THREADS 4


double sqr(double a) {
    return a * a;
}

int * calculateNumberOfRandomPointsInsideSphereForDifferentDimensions(int pointCount, double radius, int numberDimensions, int isParallel)
{ 

    srand(time(NULL));

    int * numberOfPointsInside = malloc(numberDimensions * sizeof(int));
    
    for (int i = 0; i < numberDimensions; i++) {
        numberOfPointsInside[i] = 0;
    }
    
    double sumOfSquaresOfVectorValues;
    
    double sqrRadius = radius * radius;

    int salt = clock();
    printf("%d", salt);

#pragma omp parallel for private(sumOfSquaresOfVectorValues) firstprivate(sqrRadius, radius, numberDimensions, pointCount) reduction(+:numberOfPointsInside[:numberDimensions]) if(isParallel == 1) 
    for (int i = 0; i < pointCount; i++) {
        sumOfSquaresOfVectorValues = 0;        
        unsigned int seed = 0;
        for (int j = 0; j < numberDimensions; j++) {
//            seed = (omp_get_thread_num() + i * numberDimensions * THREADS + j * THREADS) * salt;
            sumOfSquaresOfVectorValues += sqr(2 * radius * ( ( ((double) rand()) / RAND_MAX) - 0.5 ));
            if (sumOfSquaresOfVectorValues < sqrRadius) {
                numberOfPointsInside[j]++;
            } else {
                break;
            }
        }
        
    }
    
    return numberOfPointsInside;
}



int main(int argc, char *argv[])
{
    omp_set_dynamic(0);
    omp_set_num_threads(THREADS);
//TIME TEST
    printf("\n\n<<<TIME TEST>>>\n");
    double ompTime = 0;
    double antiOmpTime = 0;
    ompTime = omp_get_wtime();
    
    int * result = calculateNumberOfRandomPointsInsideSphereForDifferentDimensions(POINT_COUNT, SPHERE_RADIUS, DIMENSION_COUNT, 1);
    ompTime = omp_get_wtime() - ompTime;
    printf("dimension_number:inside:total:fill\n");
    int n = 1;
    for (int i = 0; i < DIMENSION_COUNT; i++) {
        n *= 2;
        printf("%d:%d:%d:%f\n", i + 1, result[i], POINT_COUNT, ((float) result[i] / POINT_COUNT) * n);

    } 
    antiOmpTime = clock();

    result = calculateNumberOfRandomPointsInsideSphereForDifferentDimensions(POINT_COUNT, SPHERE_RADIUS, DIMENSION_COUNT, 0);

    antiOmpTime = (clock() - antiOmpTime) / CLOCKS_PER_SEC;
    printf("dimension_number:inside:total:fill\n");
    n = 1;
    for (int i = 0; i < DIMENSION_COUNT; i++) {
        n *= 2;
        printf("%d:%d:%d:%f\n", i + 1, result[i], POINT_COUNT, ((float) result[i] / POINT_COUNT) * n);
    }

    
    printf("PARALLEL TIME: %f\n", ompTime);
    printf("NOT PARALLEL TIME: %f\n", antiOmpTime);

    return 0;   
}

