/*
    COMPILATION FLAGS: -fopenmp -lm
    
    WARNING
    Parallel is slower than not parallel
    NEED DEBUG!!!
    
*/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

#define DIMENSION_COUNT 20
#define SPHERE_RADIUS 1
#define POINT_COUNT 5000000
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
    
#pragma omp parallel for private(sumOfSquaresOfVectorValues) firstprivate(radius, numberDimensions, pointCount) reduction(+:numberOfPointsInside[:numberDimensions]) if(isParallel == 1)
    for (int i = 0; i < pointCount; i++) {
        
        sumOfSquaresOfVectorValues = 0;        
        for (int j = 0; j < numberDimensions; j++) {
            sumOfSquaresOfVectorValues += sqr(2 * radius * ( ( ((double) rand()) / RAND_MAX) - 0.5 ));
            if (sqrt(sumOfSquaresOfVectorValues) < radius) {
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
    
    int * result = calculateNumberOfRandomPointsInsideSphereForDifferentDimensions(POINT_COUNT, SPHERE_RADIUS, DIMENSION_COUNT, 1);
    printf("dimension_number:inside:total:fill\n");
    for (int i = 0; i < DIMENSION_COUNT; i++) {
        printf("%d:%d:%d:%f\n", i + 1, result[i], POINT_COUNT, ((float) result[i]) / POINT_COUNT);
    } 
    
    return 0;   
}

