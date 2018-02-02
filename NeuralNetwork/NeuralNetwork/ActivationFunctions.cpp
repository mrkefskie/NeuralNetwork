#include "ActivationFunctions.h"

float NeuralNetwork::ActivationFunctions::sign(float input)
{
	if (input >= 0) return 1.f;
	else return -1.f;
}
