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

Eigen::MatrixXd NeuralNetwork::ActivationFunctions::activate(activationFunction F, Eigen::MatrixXd x)
{
	Eigen::MatrixXd y(x.rows(), x.cols());

	for (size_t i = 0; i < x.rows(); i++)
	{
		float d = x(i, 0);
		d = activate(F, d);
		y(i, 0) = d;
	}

	return y;
}

Eigen::MatrixXd NeuralNetwork::ActivationFunctions::deActivate(activationFunction F, Eigen::MatrixXd y)
{
	Eigen::MatrixXd x(y.rows(), y.cols());

	for (size_t i = 0; i < y.rows(); i++)
	{
		float d = y(i, 0);
		d = deActivate(F, d);
		x(i, 0) = d;
	}

	return x;
}
