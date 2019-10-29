#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include <stdbool.h>
#include <stdio.h>
#include "SerialRandomNumber.h"

//bool TestMatrixOperator(struct IMatrix * m1, struct IMatrix * m2, int P);

bool TestBaselineVsSerialMatrix(int n, int seed, int A, int B, int P);

void RunTests();


#endif