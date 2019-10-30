#ifndef MATRIX_OPERATOR_H
#define MATRIX_OPERATOR_H

#include <stdlib.h>
#include <stdbool.h>

struct Matrix2x2
{
    int m[2][2];
};

struct Vector2
{
    int v[2];
};

bool compareMatrices(struct Matrix2x2 * m1, struct Matrix2x2 * m2);

struct Matrix2x2 MMmultiplyMod(struct Matrix2x2 * m1, struct Matrix2x2 * m2, int P);

struct Vector2 MVmultiplyMod(struct Vector2 * v, struct Matrix2x2 * m, int P);

#endif