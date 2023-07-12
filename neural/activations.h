#pragma once

#include "../matrix/matrix.h"

#define ALPHA 0.01

double sigmoid(double input);
Matrix* sigmoidPrime(Matrix* m);

double relu(double input);
Matrix* reluPrime(Matrix* m);

double leakeyRelu(double input);
Matrix* leakeyReluPrime(Matrix* m);

Matrix* softmax(Matrix* m);