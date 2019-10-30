#include "ParallelTestSuite.h"


bool TestParallelPrefix(struct Matrix2x2 * m, int procs, int my_rank, int P)
{
    struct Matrix2x2 my_offset = ParallelPrefix(m, procs, my_rank, P);

    struct Matrix2x2 serial_result = *m;
    int i;
    for(i = 0; i < my_rank; i++)
    {
        serial_result = MMmultiplyMod(&serial_result, m, P);
    }

    printf("My rank %d serial: A=%d B=%d C=%d D=%d   parallel: A=%d B=%d C=%d D=%d\n", my_rank, serial_result.m[0][0],
    serial_result.m[1][0], serial_result.m[0][1], serial_result.m[1][1], my_offset.m[0][0], my_offset.m[1][0], 
    my_offset.m[0][1], my_offset.m[1][1]);

    return compareMatrices(&serial_result, &my_offset);
}