#ifndef __NN_ACTIVATIONFUNCTION_H
#define __NN_ACTIVATIONFUNCTION_H

#include <math.h>

#include <Eigen\Dense>

namespace NeuralNetwork
{
	typedef enum
	{
		SIGMOID_ACTIVATION,
		TANH_ACTIVATION,
		SIGN_ACTIVATION
	} activationFunction;

	class ActivationFunctions
	{
	public:
		static float activate(activationFunction F, float x);
		static float deActivate(activationFunction F, float y);

		static Eigen::MatrixXd activate(activationFunction F, Eigen::MatrixXd x);
		static Eigen::MatrixXd deActivate(activationFunction F, Eigen::MatrixXd y);

	private:
		static float sigmoid(float x)
		{
			return 1 / (1 + exp(-x));
		}
		static float deSigmoid(float y)
		{
			return y * (1 - y);
		}

		static float acTanh(float x)
		{
			return tanh(x);
		}
		static float acDeTanh(float y)
		{
			return 1 - (y * y);
		}

		static float sign(float input)
		{
			if (input >= 0) return 1.f;
			else return -1.f;
		}
	};
}

#endif // __NN_ACTIVATIONFUNCTION_H
