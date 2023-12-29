#pragma once

#include "../matrix/matrix.h"

#define ALPHA 0.01

double sigmoid(double input);
matrix* sigmoidPrime(matrix* m);

double relu(double input);
matrix* reluPrime(matrix* m);

double tanh(double input);
matrix* tanhPrime(matrix* m);

double logistic(double input);
matrix* logisticPrime(matrix* m);

double leakeyRelu(double input);
matrix* leakeyReluPrime(matrix* m);

matrix* softmax(matrix* m);