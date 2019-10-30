#include "MatrixOperator.h"

bool compareMatrices(struct Matrix2x2 * m1, struct Matrix2x2 * m2)
{
    if(m1->m[0][0] != m2->m[0][0])
        return false;
    if(m1->m[1][0] != m2->m[1][0])
        return false;
    if(m1->m[0][1] != m2->m[0][1])
        return false;
    if(m1->m[1][1] != m2->m[1][1])
        return false;

    return true;
}


struct Matrix2x2 MMmultiplyMod(struct Matrix2x2 * m1, struct Matrix2x2 * m2, int P)
{
    struct Matrix2x2 * result = malloc(sizeof(struct Matrix2x2));
    
    result->m[0][0] = (m1->m[0][0]*m2->m[0][0] + m1->m[0][1]*m2->m[1][0]) % P;
    result->m[1][0] = (m1->m[1][0]*m2->m[0][0] + m1->m[1][1]*m2->m[1][0]) % P;
    result->m[0][1] = (m1->m[0][0]*m2->m[0][1] + m1->m[0][1]*m2->m[1][1]) % P;
    result->m[1][1] = (m1->m[1][0]*m2->m[0][1] + m1->m[1][1]*m2->m[1][1]) % P; 

    return *result;
}


struct Vector2 MVmultiplyMod(struct Vector2 * v, struct Matrix2x2 * m, int P)
{
    struct Vector2 result;

    result.v[0] = (v->v[0] * m->m[0][0] + v->v[1] * m->m[1][0]) % P;
    result.v[1] = (v->v[0] * m->m[0][1] + v->v[1] * m->m[1][1]) % P;

    return result;
}