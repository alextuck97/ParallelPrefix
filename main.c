#include "ParallelPrefix.h" 
#include "SerialRandomNumber.h"
#include <stdio.h>

int main(int argc,char *argv[])
{

    int rank,procs;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);

    char * end = NULL;
    
    int seed = strtol(argv[1], &end, 10);
    int A = strtol(argv[2], &end, 10);
    int B = strtol(argv[3], &end, 10);
    int P = strtol(argv[4], &end, 10);
    int n = strtol(argv[5], &end, 10);
    
    struct Matrix2x2 m;
    m.m[0][0] = A;
    m.m[1][0] = B;
    m.m[0][1] = 0;
    m.m[1][1] = 1;
    
    struct Matrix2x2 offset = m;

    int i;
    //Condition gives rank 0's offset to be m, while all other ranks are M^n/p
    for(i = 0; i < rank*n/procs - (rank - 1)*n/procs - 1; i++)
    {
        offset = MMmultiplyMod(&offset, &m, P);
    }
    
    offset = ParallelPrefix(&offset, procs, rank, P);

    struct Vector2 v;
    v.v[0] = seed;
    v.v[1] = 0;

    int * output = malloc(sizeof(int) * n/procs);
    for(i = 0; i < n / procs; i++)
    {
        output[i] = MVmultiplyMod(&v, &offset, P).v[0];
        offset = MMmultiplyMod(&m,&offset, P);
    }
    printf("Rank %d : ", rank);
    for(i = 0; i < n / procs; i++)
    {
        printf("%d ", output[i]);
    }
    printf("\n");
    free(output);

    MPI_Finalize();

    int * serial_output = serialBaseline(n, seed, A, B, P);
    printf("Serial Results: \n");
    for(i = 0; i < procs; i++)
    {
        printf("Rank %d: ", i);
        int j;
        for(j = 0; j < n / procs; j++)
        {
            printf("%d ", serial_output[i * n / procs + j]);
        }
        printf("\n");
    } 
    free(serial_output);
}