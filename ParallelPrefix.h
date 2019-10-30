#ifndef PARALLEL_PREFIX_H
#define PARALLEL_PREFIX_H

#include <math.h>
#include <mpi.h>
#include "MatrixOperator.h"

struct Matrix2x2 ParallelPrefix(struct Matrix2x2 M, int procs, int my_rank, int P);

#endif