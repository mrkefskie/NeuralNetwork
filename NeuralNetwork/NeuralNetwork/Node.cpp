#include "Node.h"

NeuralNetwork::Node::Node(unsigned long amountOfInputs, ACTIVATION_TYPE type, float learningRate) : _inputs(amountOfInputs + 1), _activationType(type), _learningRate(learningRate)
{
	srand(time(NULL));
	_weights = (float*)malloc(sizeof(float) * _inputs);
	for (unsigned long i = 0; i < _inputs; i++)
	{
		_weights[i] = (rand() / (float)RAND_MAX * 2) - 1.f;
	}
}

NeuralNetwork::Node::~Node()
{
	//free(_weights);
}


float NeuralNetwork::Node::guess(float* inputs)
{
	float sum = 0.f;
	float output = 0.f;

	for (unsigned long i = 0; i < _inputs; i++)
	{
		sum += inputs[i] * _weights[i];
	}

	switch (_activationType)
	{
	case SIGN:
		output = ActivationFunctions::sign(sum);
		break;
	default:
		break;
	}

	return output;
}

void NeuralNetwork::Node::train(float* inputs, float target)
{
	float g = guess(inputs);
	float e = target - g;

	if (g != target)
	{
		e += 0;
	}

	for (unsigned long i = 0; i < _inputs; i++)
	{
		_weights[i] += e * inputs[i] * _learningRate;
	}
}
