#include <iostream>
#include <stdio.h>
#include <cmath>

#include "mpi.h"

using namespace std;

#define N 12

int main (int argc, char **argv)
{
    MPI_Init(&argc, &argv);

    int my_rank;
    int all_count;
    int tagMessage = 1;
    int sender_rank = 0;

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size (MPI_COMM_WORLD, &all_count);

    printf("%d:all_count %d\n", my_rank, all_count);
    int part_array_size = (N / all_count);
    int ** part_arrays = new int * [all_count];

    if (my_rank == sender_rank) {
        int * a = (int *) malloc (sizeof(int) * N);
        for (int i = 0; i < N; i++) {
           a[i] = 2 * i;
        }
        for (int i = 0; i < all_count; i++) {
            part_arrays[i] = (int * ) malloc (sizeof(int) * part_array_size);
            for (int j = 0; j < part_array_size; j++) {
                part_arrays[i][j] = a[i * part_array_size + j];
            }
            if (i != sender_rank) {
            MPI_Send(part_arrays[i], part_array_size, MPI_INT, i, tagMessage, MPI_COMM_WORLD);
            }
        }
    }
    int bufElems;
    int * b;
    if (my_rank != sender_rank) {

        MPI_Status status;
        MPI_Status status2;
        MPI_Probe(MPI_ANY_SOURCE, tagMessage, MPI_COMM_WORLD, &status);
        MPI_Get_count(&status, MPI_INT, &bufElems);
    
        b = (int * ) malloc(sizeof(int) * bufElems);
        MPI_Recv(b, bufElems, MPI_INT, MPI_ANY_SOURCE, tagMessage, MPI_COMM_WORLD, &status2);
    } else {
        b = part_arrays[sender_rank];
        bufElems = part_array_size;
    }
    for (int i = 0; i < bufElems; i++) {
        printf("%d: %d\n", my_rank, b[i]);
    }
        
    MPI_Finalize();
    return 0;
}
