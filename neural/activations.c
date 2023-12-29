#include "activations.h"

#include <math.h>
#include "../matrix/ops.h"

double sigmoid(double input)
{
	return 1.0 / (1 + exp(-1 * input));
}
double relu(double input)
{
	return (input > 0) ? input : 0.0;
}
double leakeyRelu(double input)
{
	return (input > 0) ? input : ALPHA * input;
}
double logistic(double input) {
    return 1.0 / (1.0 + exp(-input));
}
double tanh(double input) {
    return tanh(input);
}

matrix* logisticPrime(matrix* m) {
    matrix* mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[i][j] = logistic(m->entries[i][j]);
        }
    }
    return mat;
}

matrix* tanhPrime(matrix* m) {
    matrix* mat = matrix_create(m->rows, m->cols);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            mat->entries[i][j] = tanh(m->entries[i][j]);
        }
    }
    return mat;
}

matrix* leakeyReluPrime(matrix* m)
{
	matrix *mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			mat->entries[i][j] = (m->entries[i][j] < 0) ? m->entries[i][j] * ALPHA : m->entries[i][j];
		}
	}
	return mat;
}


matrix *sigmoidPrime(matrix *m)
{
	matrix *ones = matrix_create(m->rows, m->cols);
	matrix_fill(ones, 1);
	matrix *subtracted = subtract(ones, m);
	matrix *multiplied = multiply(m, subtracted);
	matrix_free(ones);
	matrix_free(subtracted);
	return multiplied;
}

matrix *reluPrime(matrix *m)
{
	matrix *mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			mat->entries[i][j] = (m->entries[i][j] < 0) ? 0 : m->entries[i][j];
		}
	}
	return mat;
}

matrix *softmax(matrix *m)
{
	double total = 0;
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			total += exp(m->entries[i][j]);
		}
	}
	matrix *mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < mat->rows; i++)
	{
		for (int j = 0; j < mat->cols; j++)
		{
			mat->entries[i][j] = exp(m->entries[i][j]) / total;
		}
	}
	return mat;
}