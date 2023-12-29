#include "nn.h"
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../matrix/ops.h"
#include "../neural/activations.h"

#define MAXCHAR 1000

// 784, 300, 10
NeuralNetwork* network_create(int input, int hidden, int output, double lr) {
	NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
	net->input = input;
	net->hidden = hidden;
	net->output = output;
	net->learning_rate = lr;
	matrix* hidden_layer = matrix_create(hidden, input);
	matrix* output_layer = matrix_create(output, hidden);
	matrix_randomize(hidden_layer, hidden);
	matrix_randomize(output_layer, output);
	net->hidden_weights = hidden_layer;
	net->output_weights = output_layer;
	return net;
}

void network_train(NeuralNetwork* net, matrix* input, matrix* output , matrix* (*func0)(matrix*) , double (*func1)(double)) {
	// Feed forward
	matrix* hidden_inputs	= dot(net->hidden_weights, input);
	matrix* hidden_outputs = apply(func1, hidden_inputs);
	matrix* final_inputs = dot(net->output_weights, hidden_outputs);
	matrix* final_outputs = apply(func1, final_inputs);

	// Find errors
	matrix* output_errors = subtract(output, final_outputs);
	matrix* transposed_mat = transpose(net->output_weights);
	matrix* hidden_errors = dot(transposed_mat, output_errors);
	matrix_free(transposed_mat);


	matrix* relu_mat = (*func0)(final_outputs);
	matrix* multiplied_mat = multiply(output_errors, relu_mat);
	transposed_mat = transpose(hidden_outputs);
	matrix* dot_mat = dot(multiplied_mat, transposed_mat);
	matrix* scaled_mat = scale(net->learning_rate, dot_mat);
	matrix* added_mat = add(net->output_weights, scaled_mat);

	matrix_free(net->output_weights); // Free the old weights before replacing
	net->output_weights = added_mat;

	matrix_free(relu_mat);
	matrix_free(multiplied_mat);
	matrix_free(transposed_mat);
	matrix_free(dot_mat);
	matrix_free(scaled_mat);

	// Reusing variables after freeing memory
	relu_mat = (*func0)(hidden_outputs);
	multiplied_mat = multiply(hidden_errors, relu_mat);
	transposed_mat = transpose(input);
	dot_mat = dot(multiplied_mat, transposed_mat);
	scaled_mat = scale(net->learning_rate, dot_mat);
	added_mat = add(net->hidden_weights, scaled_mat);
	matrix_free(net->hidden_weights); // Free the old hidden_weights before replacement
	net->hidden_weights = added_mat; 

	matrix_free(relu_mat);
	matrix_free(multiplied_mat);
	matrix_free(transposed_mat);
	matrix_free(dot_mat);
	matrix_free(scaled_mat);

	// Free matrices
	matrix_free(hidden_inputs);
	matrix_free(hidden_outputs);
	matrix_free(final_inputs);
	matrix_free(final_outputs);
	matrix_free(output_errors);
	matrix_free(hidden_errors);
}
void displayProgressBar(int progress) {
    int barWidth = 100;
    int filledWidth = (progress * barWidth) / 100;

    printf("Progress: %d%% [", progress);
    for (int i = 0; i < filledWidth; i++) {
        printf("=");
    }
    for (int i = filledWidth; i < barWidth; i++) {
        printf(" ");
    }
    printf("]\n");
}
void network_train_batch_imgs(NeuralNetwork* net, Img** imgs, int batch_size ,matrix* (*func0)(matrix*) , double (*func1)(double)) {
	for (int i = 0; i < batch_size; i++) {

		if (i % 100 == 0)
		{
			int progress = (i * 100) / batch_size;
            displayProgressBar(progress);
		}
		Img* cur_img = imgs[i];
		matrix* img_data = matrix_flatten(cur_img->img_data, 0); // 0 = flatten to column vector
		matrix* output = matrix_create(10, 1);
		output->entries[cur_img->label][0] = 1; // Setting the result
		network_train(net, img_data, output , (*func0) , (*func1));
		matrix_free(output);
		matrix_free(img_data);
	}
}

matrix* network_predict_img(NeuralNetwork* net, Img* img , double (*func)(double)) {
	matrix* img_data = matrix_flatten(img->img_data, 0);
	matrix* res = network_predict(net, img_data , (*func) );
	matrix_free(img_data);
	return res;
}

double network_predict_imgs(NeuralNetwork* net, Img** imgs, int n , double (*func)(double)) {
	int n_correct = 0;
	for (int i = 0; i < n; i++) {
		matrix* prediction = network_predict_img(net, imgs[i] , (*func));
		if (matrix_argmax(prediction) == imgs[i]->label) {
			n_correct++;
		}
		matrix_free(prediction);
	}
	return 1.0 * n_correct / n;
}

matrix* network_predict(NeuralNetwork* net, matrix* input_data , double (*func)(double)) {
	matrix* hidden_inputs	= dot(net->hidden_weights, input_data);
	matrix* hidden_outputs = apply((*func), hidden_inputs);
	matrix* final_inputs = dot(net->output_weights, hidden_outputs);
	matrix* final_outputs = apply((*func), final_inputs);
	matrix* result = softmax(final_outputs);

	matrix_free(hidden_inputs);
	matrix_free(hidden_outputs);
	matrix_free(final_inputs);
	matrix_free(final_outputs);

	return result;
}

void network_save(NeuralNetwork* net, char* file_string) {
	mkdir(file_string, 0777);
	// Write the descriptor file
	chdir(file_string);
	FILE* descriptor = fopen("descriptor", "w");
	fprintf(descriptor, "%d\n", net->input);
	fprintf(descriptor, "%d\n", net->hidden);
	fprintf(descriptor, "%d\n", net->output);
	fclose(descriptor);
	matrix_save(net->hidden_weights, "hidden");
	matrix_save(net->output_weights, "output");
	printf("Successfully written to '%s'\n", file_string);
	chdir("-"); // Go back to the orignal directory
}

NeuralNetwork* network_load(char* file_string) {
	NeuralNetwork* net = malloc(sizeof(NeuralNetwork));
	char entry[MAXCHAR];
	chdir(file_string);

	FILE* descriptor = fopen("descriptor", "r");
	fgets(entry, MAXCHAR, descriptor);
	net->input = atoi(entry);
	fgets(entry, MAXCHAR, descriptor);
	net->hidden = atoi(entry);
	fgets(entry, MAXCHAR, descriptor);
	net->output = atoi(entry);
	fclose(descriptor);
	net->hidden_weights = matrix_load("hidden");
	net->output_weights = matrix_load("output");
	printf("Successfully loaded network from '%s'\n", file_string);
	chdir("-"); // Go back to the original directory
	return net;
}

void network_print(NeuralNetwork* net) {
	printf("# of Inputs: %d\n", net->input);
	printf("# of Hidden: %d\n", net->hidden);
	printf("# of Output: %d\n", net->output);
	printf("Hidden Weights: \n");
	matrix_print(net->hidden_weights);
	printf("Output Weights: \n");
	matrix_print(net->output_weights);
}

void network_free(NeuralNetwork *net) {
	matrix_free(net->hidden_weights);
	matrix_free(net->output_weights);
	free(net);
	net = NULL;
}
NeuralNetwork * Load_NetWork(char * hidden_weights , char * output_weights , int LR)
{
	NeuralNetwork *net = network_create(784, 300, 10, LR);
	net->hidden_weights = matrix_load(hidden_weights);
	net->output_weights = matrix_load(output_weights);
	return net;
}