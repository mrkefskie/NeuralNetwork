#include "ActivationFunctions.h"

float NeuralNetwork::ActivationFunctions::activate(activationFunction F, float x)
{
	switch (F)
	{
	case SIGMOID_ACTIVATION:
		return sigmoid(x);
	case TANH_ACTIVATION:
		return acTanh(x);
	case SIGN_ACTIVATION:
		return sign(x);
	default:
		return 0.f;
		break;
	}
}

float NeuralNetwork::ActivationFunctions::deActivate(activationFunction F, float y)
{
	switch (F)
	{
	case SIGMOID_ACTIVATION:
		return deSigmoid(y);
	case TANH_ACTIVATION:
		return acDeTanh(y);
	default:
		return 0.f;
		break;
	}
}