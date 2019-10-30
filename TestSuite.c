#include "TestSuite.h"

bool TestMatrixOperator(struct Matrix2x2 * m1, struct Matrix2x2 * m2, int P, struct Matrix2x2 * precalced_result)
{
    struct Matrix2x2 identity;
    identity.m[0][0] = 1;
    identity.m[0][1] = 0;
    identity.m[1][0] = 0;
    identity.m[1][1] = 1;

    struct Matrix2x2 result = MMmultiplyMod(m1, &identity, P);

    if(!compareMatrices(&result, m1))
        return false;
    
    result = MMmultiplyMod(m1, m2, P);
    if(!compareMatrices(&result, precalced_result))
        return false;

    return true;
}


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


bool TestBaselineVsOffsetMatrix(int n, int seed, int A, int B, int P)
{
    int * serial_result = serialBaseline(n, seed, A, B, P);
    struct Matrix2x2 offset;
    offset.m[0][0] = A;
    offset.m[1][0] = B;
    offset.m[0][1] = 0;
    offset.m[1][1] = 1;
    int * offset_mat_result = matrixBaselineOffset(n, seed, P, offset);

    int i = 0;
    for(; i < n; i++)
    {
        if(serial_result[i] != offset_mat_result[i])
        {
            free(serial_result);
            free(offset_mat_result);
            return false;
        }
    }

    free(serial_result);
    free(offset_mat_result);
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

    if(TestBaselineVsOffsetMatrix(40, 3, 53, 22, 7477))
    {
        printf("SUCCESS: Serial and Offset serial matrix\n");
    }
    else
    {
        printf("FAILURE: Serial and Offset serial matrix\n");
    }
    
    struct Matrix2x2 m1, m2, result;
    m1.m[0][0] = 10;
    m1.m[1][0] = 22;
    m1.m[0][1] = 14;
    m1.m[1][1] = 5;
    m2.m[0][0] = 2;
    m2.m[1][0] = 99;
    m2.m[0][1] = 42;
    m2.m[1][1] = 11;
    result.m[0][0] = 1406;
    result.m[1][0] = 539;
    result.m[0][1] = 574;
    result.m[1][1] = 979;
    if(TestMatrixOperator(&m1, &m2, 7477, &result))
    {
        printf("SUCCESS: Matrix multiplication worked as intended\n");
    }
    else
    {
        printf("FAILURE: Matrix multiplication went wrong somewhere\n");
    }
}