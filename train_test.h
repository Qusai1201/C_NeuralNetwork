#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "util/img.h"
#include "neural/activations.h"
#include "neural/nn.h"
#include "matrix/matrix.h"
#include "matrix/ops.h"

#define number_train_imgs 60000
#define number_test_imgs 10000
#define LR 0.01

void train_test()
{
	
	Img **imgs = csv_to_imgs("data/mnist_train.csv", number_train_imgs);
	Img **test_imgs = csv_to_imgs("data/mnist_test.csv", number_test_imgs);

	NeuralNetwork *net = network_create(784, 300, 10, LR);
	NeuralNetwork *BestNet = network_create(784, 300, 10, LR);

	double BestScore = 0;

	for (size_t i = 0; i < 10; i++)
	{
		network_train_batch_imgs(net, imgs, number_train_imgs ,leakeyReluPrime, leakeyRelu);
		double score = network_predict_imgs(net, test_imgs, number_test_imgs, leakeyRelu);
		printf("Score: %1.5f\n", score);
		if(score > BestScore)
		{
			BestNet->hidden_weights = net->hidden_weights;
			BestNet->output_weights = net->output_weights;
			BestScore = score;
		}

	}
	
	printf("Score: %1.5f\n", BestScore);


	network_save(BestNet , "model");


	imgs_free(imgs, number_train_imgs);
	imgs_free(test_imgs, number_test_imgs);
	
	network_free(net);
}

