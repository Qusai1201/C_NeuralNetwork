#pragma once

#include "matrix.h"

matrix* multiply(matrix* m1, matrix* m2);
matrix* add(matrix* m1, matrix* m2);
matrix* subtract(matrix* m1, matrix* m2);
matrix* dot(matrix* m1, matrix* m2);
matrix* apply(double (*func)(double), matrix* m);
matrix* scale(double n, matrix* m);
matrix* addScalar(double n, matrix* m);
matrix* transpose(matrix* m);
