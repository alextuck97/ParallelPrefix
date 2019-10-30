#ifndef SERIAL_RANDOM_NUMBER_H
#define SERIAL_RANDOM_NUMBER_H

#include <stdlib.h>
#include <math.h>
#include "MatrixOperator.h"

int * serialBaseline(int n, int seed, int A, int B, int P);

int * matrixBaseline(int n, int seed, int A, int B, int P);

int * matrixBaselineOffset(int n, int seed, int P, struct Matrix2x2 offset);




#endif