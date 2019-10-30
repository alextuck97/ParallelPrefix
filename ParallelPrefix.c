#include "ParallelPrefix.h"

struct Matrix2x2 ParallelPrefix(struct Matrix2x2 * M, int procs, int my_rank, int P)
{
    struct Matrix2x2 local = *M;
    struct Matrix2x2 offset = *M;

    if(procs == 1)
        return M;
    
    int i;
    for(i = 0; i < log2f((float)procs); i++)
    {
        int toggle = (int)(pow(2, i)+0.5);
        int partner = my_rank ^ toggle;

        MPI_Send(&offset.m[0][0], 4, MPI_INT, partner, 0, MPI_COMM_WORLD);
        
        MPI_STATUS status;
        struct Matrix2x2 offset_remote;
        MPI_Recv(&offset_remote.m[0][0], 4, MPI_INT, partner, 0, MPI_COMM_WORLD, &status);

        if(partner < my_rank)
        {
            offset = MMmultiplyMod(&offset_remote, &offset, P);
        }
    }

    return offset;
}