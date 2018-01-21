#include "Perceptron.h"


int sign(float n)
{
	if (n >= 0) return 1;
	else return -1;
}


Perceptron::Perceptron()
{
	srand(time(NULL));

	for (size_t i = 0; i < AMOUNT_OF_INPUTS; i++)
	{
		weights[i] = (rand() / (float)RAND_MAX * 2) - 1.f;
	}
}


Perceptron::~Perceptron()
{
}

int Perceptron::guess(float inputs[AMOUNT_OF_INPUTS])
{
	float sum = 0;
	for (size_t i = 0; i < AMOUNT_OF_INPUTS; i++)
	{
		sum += inputs[i] * weights[i];
	}

	int output = sign(sum);

	return output;
}

void Perceptron::train(float inputs[AMOUNT_OF_INPUTS], int target)
{
	int guess = this->guess(inputs);

	int error = target - guess;

	for (size_t i = 0; i < AMOUNT_OF_INPUTS; i++)
	{
		weights[i] += error * inputs[i] * LEARNING_RATE;
	}
}
