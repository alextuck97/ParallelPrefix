#include "SerialRandomNumber.h"

int * serialBaseline(int n, int seed, int A, int B, int P)
{
    int * result = malloc(sizeof(int) * n);
    
    int prev_val = seed;

    int i = 0;
    for(;i < n; i++)
    {
        prev_val = (A*prev_val + B) % P;
        result[i] = prev_val;
    }

    return result;
}

int * matrixBaseline(int n, int seed, int A, int B, int P)
{
    int * result = malloc(sizeof(int) * n);

    struct Matrix2x2 m1;
    m1.m[0][0] = A;
    m1.m[1][0] = B;
    m1.m[0][1] = 0;
    m1.m[1][1] = 1;

    struct Vector2 prev_val;
    prev_val.v[0] = seed;
    prev_val.v[1] = 1;

    int i = 0;
    for(; i < n; i++)
    {
        prev_val = MVmultiplyMod(&prev_val, &m1, P);
        result[i] = prev_val.v[0];
    }

    return result;
}

int * matrixBaselineOffset(int n, int seed, int P, struct Matrix2x2 offset)
{
    int * result = malloc(sizeof(int) * n);
    
    struct Vector2 prev_val;
    prev_val.v[0] = seed;
    prev_val.v[1] = 1;

    int i = 0;
    for(; i < n; i++)
    {
        prev_val = MVmultiplyMod(&prev_val, &offset, P);
        result[i] = prev_val.v[0];
    }

    return result;

}