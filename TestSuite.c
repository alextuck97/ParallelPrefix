#include "TestSuite.h"

bool TestBaselineVsSerialMatrix(int n, int seed, int A, int B, int P)
{
    int * serial_result = serialBaseline(n, seed, A, B, P);
    int * matrix_result = matrixBaseline(n, seed, A, B, P);
 
    int i = 0;
    for(; i < n; i++)
    {
        if(serial_result[i] != matrix_result[i])
        {
            free(serial_result);
            free(matrix_result);
            return false;
        }
    }

    free(serial_result);
    free(matrix_result);
    return true;
}


void RunTests()
{
    if(TestBaselineVsSerialMatrix(40, 3, 53, 22, 7477))
    {
        printf("SUCCESS: Serial and Matrix baseline\n");
    }
    else
    {
        printf("FAILED: Serial and Matrix baseline\n");
    }
}