#pragma once

#include "../matrix/matrix.h"

#define ALPHA 0.01

double sigmoid(double input);
Matrix* sigmoidPrime(Matrix* m);

double logistic(double input);
double logisticPrime(Matrix* m);

double relu(double input);
Matrix* reluPrime(Matrix* m);

double tanh(double input);
Matrix* tanhPrime(Matrix* m);

double leakeyRelu(double input);
Matrix* leakeyReluPrime(Matrix* m);

Matrix* softmax(Matrix* m);