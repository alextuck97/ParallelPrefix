#include "MatrixOperator.h"

struct Matrix2x2 MMmultiplyMod(struct Matrix2x2 * m1, struct Matrix2x2 * m2, int P)
{
    struct Matrix2x2 * result = malloc(sizeof(struct Matrix2x2));
    
    return *result;
}


struct Vector2 MVmultiplyMod(struct Vector2 * v, struct Matrix2x2 * m, int P)
{
    struct Vector2 result;

    result.v[0] = (v->v[0] * m->m[0][0] + v->v[1] * m->m[1][0]) % P;
    result.v[1] = (v->v[0] * m->m[0][1] + v->v[1] * m->m[1][1]) % P;

    return result;
}