#include <iostream>
#include <stdio.h>
#include <cmath>

#include "mpi.h"

using namespace std;

#define N 10

int main (int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int my_rank;
    int all_count;
    int tagMessage = 1;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &all_count);

    int * a;
    a = (int * ) malloc (sizeof(int));

    for (int i = 0; i < N; i++) {
        a[i] = i * i;
    }

    if (my_rank == 1) {
        for (int i = 0; i < all_count; i++) {
            if (i != my_rank) {
                MPI_Send(a, N, MPI_INT, i, tagMessage, MPI_COMM_WORLD);
            }
        }
    } else {
        MPI_Status status;
        MPI_Status status2;
        MPI_Probe(MPI_ANY_SOURCE, tagMessage, MPI_COMM_WORLD, &status);
        int bufElems;
        MPI_Get_count(&status, MPI_INT, &bufElems);
        int * b;
        b = (int * ) malloc(sizeof(int) * bufElems);
        MPI_Recv(b, bufElems, MPI_INT, MPI_ANY_SOURCE, tagMessage, MPI_COMM_WORLD, &status2);
        
        for (int i = 0; i < bufElems; i++) {
            printf("%d: %d\n", my_rank, b[i]);
        }
        
    }

    MPI_Finalize();
    return 0;
}
