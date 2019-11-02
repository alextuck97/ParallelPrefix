#include "ParallelPrefix.h" 
#include "SerialRandomNumber.h"
#include <stdio.h>
#include <sys/time.h>

/****************
 * Five command line arguments 
 * Seed: seed of the random number generator
 * A: First parameter to the random number generator
 * B: Second parameter to the random number generator
 * P: Prime number for the random number generator
 * n: How many random numbers to generate. Make sure n
 *    is a multiple of the total number of processes
 * ************/

int main(int argc,char *argv[])
{

    int rank,procs;

    struct timeval t1, t2;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&procs);

    char * end = NULL;
    
    int seed = strtol(argv[1], &end, 10);
    int A = strtol(argv[2], &end, 10);
    int B = strtol(argv[3], &end, 10);
    int P = strtol(argv[4], &end, 10);
    //int n = strtol(argv[5], &end, 10);
    
    struct Matrix2x2 m;
    m.m[0][0] = A;
    m.m[1][0] = B;
    m.m[0][1] = 0;
    m.m[1][1] = 1;
    
    struct Matrix2x2 offset = m;
    
   
    //The maximum numbers generated will be 64*2^(q-1)
    int q = 18;
    int s;
    for(s = 0; s < q; s++)
    {
        int n = 64 * pow((double)2, (double)s);

        //Do 10 trials generating n numbers
        int trials = 10;
        int time_sum = 0;
        int j;
        for(j = 0; j < trials; j++)
        {
            gettimeofday(&t1, NULL);
            //Execute the serial code if procs is 1
            if(procs == 1)
            {
                int * output = serialBaseline(n, seed, A, B, P);
                free(output);
            }
            else
            {
                int i;
                //Condition gives rank 0's offset to be m, while all other ranks are M^n/p
                if(rank != 0)
                {
                    for(i = 0; i < n/procs - 1; i++)
                    {
                        offset = MMmultiplyMod(&offset, &m, P);
                    }
                }
                offset = ParallelPrefix(&offset, procs, rank, P);

                struct Vector2 v;
                v.v[0] = seed;
                v.v[1] = 1;

                int * output = malloc(sizeof(int) * n/procs);
                for(i = 0; i < n / procs; i++)
                {
                    output[i] = MVmultiplyMod(&v, &offset, P).v[0];
                    offset = MMmultiplyMod(&m,&offset, P);
                }
                free(output);
            
            }
        
            gettimeofday(&t2, NULL);
            time_sum += (t2.tv_sec-t1.tv_sec)*1000000 + (t2.tv_usec-t1.tv_usec)/1000000;
        
        }
        if(rank == 0)
        {
            float time_avg = (float)time_sum / trials;
            printf("%f ", time_avg);
        }
        
    }
    if(rank == 0)
    {
        printf("\n");
    }
   

    MPI_Finalize();   
}