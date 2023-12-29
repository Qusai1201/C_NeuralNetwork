#pragma once

#include "../matrix/matrix.h"
#include "../util/img.h"

typedef struct {
	int input;
	int hidden;
	int output;
	double learning_rate;
	matrix* hidden_weights;
	matrix* output_weights;
} NeuralNetwork;

NeuralNetwork* network_create(int input, int hidden, int output, double lr);
void network_train(NeuralNetwork* net, matrix* input, matrix* output , matrix* (*func0)(matrix*) , double (*func1)(double));
void network_train_batch_imgs(NeuralNetwork* net, Img** imgs, int batch_size ,matrix* (*func0)(matrix*) , double (*func1)(double));
matrix* network_predict_img(NeuralNetwork* net, Img* img , double (*func)(double));
double network_predict_imgs(NeuralNetwork* net, Img** imgs, int n , double (*func)(double));
matrix* network_predict(NeuralNetwork* net, matrix* input_data , double (*func)(double));
void network_save(NeuralNetwork* net, char *);
NeuralNetwork* network_load(char* file_string);
void network_print(NeuralNetwork* net);
void network_free(NeuralNetwork* net);
NeuralNetwork * Load_NetWork(char * hidden_weights , char * output_weights , int LR);