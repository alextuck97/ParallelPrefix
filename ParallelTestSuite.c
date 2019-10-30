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

    return compareMatrices(&serial_result, &my_offset);
}