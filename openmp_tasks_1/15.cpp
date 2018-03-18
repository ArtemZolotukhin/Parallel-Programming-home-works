#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>

#define NUM_THREADS 4

static int compareFunc (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}

using namespace std;


int main() {
    
    omp_set_dynamic(0); // not change number of threads when running
    omp_set_num_threads(NUM_THREADS);
    
    int start = 0;
    
    int end = 0;
    
    printf("Start: ");
    cin >> start;
    
    printf("End: ");
    cin >> end;
        
    vector<int> result;
    
    bool isSimple = true;
    int rightBound = 0;
    #pragma omp parallel for private(isSimple, rightBound)
    for (int i = start; i <= end; i++) {
        isSimple = true;
        rightBound = sqrt(i);
        for (int j = 2; j <= rightBound; j++) {
            if (i > 2) {
                if (i % j == 0) {
                    isSimple = false;
                    break;
                }
            }
        }
        if (isSimple) {
            #pragma omp critical
            {
                result.insert(result.end(), i);
            }
        }
    }

    //SORT IT
    sort (result.begin(), result.end());

    for (int i = 0; i < result.size(); i++) {
        printf("%d ", result[i]);
    }

    return 0;
}


