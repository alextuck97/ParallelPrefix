#include "ParallelTestSuite.h"

int main(int argc,char *argv[])
{

    int rank,p;
  

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);

    printf("my rank=%d\n",rank);
    printf("Rank=%d: number of processes =%d\n",rank,p);

    struct Matrix2x2 m;
    m.m[0][0] = 5;
    m.m[1][0] = 22;
    m.m[0][1] = 96;
    m.m[1][1] = 12;

    bool b = TestParallelPrefix(&m, p, rank, 7477);
    bool result;

    MPI_Allreduce(&b, &result, 1, MPI_C_BOOL, MPI_LAND, MPI_COMM_WORLD);
    if(rank == p - 1)
    {
        if(result)
            printf("SUCCESS: Parallel prefix worked. Each process got its expected matrix.\n");
        else
        {
            printf("FAILURE: Parallel prefix did not work. At least one process did not get the right matrix.\n");
        }
        
            
    }

    MPI_Finalize();

}