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

Matrix* leakeyReluPrime(Matrix* m)
{
	Matrix *mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			mat->entries[i][j] = (m->entries[i][j] < 0) ? m->entries[i][j] * ALPHA : m->entries[i][j];
		}
	}
	return mat;
}


Matrix *sigmoidPrime(Matrix *m)
{
	Matrix *ones = matrix_create(m->rows, m->cols);
	matrix_fill(ones, 1);
	Matrix *subtracted = subtract(ones, m);
	Matrix *multiplied = multiply(m, subtracted);
	matrix_free(ones);
	matrix_free(subtracted);
	return multiplied;
}

Matrix *reluPrime(Matrix *m)
{
	Matrix *mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			mat->entries[i][j] = (m->entries[i][j] < 0) ? 0 : m->entries[i][j];
		}
	}
	return mat;
}

Matrix *softmax(Matrix *m)
{
	double total = 0;
	for (int i = 0; i < m->rows; i++)
	{
		for (int j = 0; j < m->cols; j++)
		{
			total += exp(m->entries[i][j]);
		}
	}
	Matrix *mat = matrix_create(m->rows, m->cols);
	for (int i = 0; i < mat->rows; i++)
	{
		for (int j = 0; j < mat->cols; j++)
		{
			mat->entries[i][j] = exp(m->entries[i][j]) / total;
		}
	}
	return mat;
}