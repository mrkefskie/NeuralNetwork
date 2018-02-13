#ifndef _NN_SIMPLENETWORK_H
#define _NN_SIMPLENETWORK_H

//#include <Matrix\Matrix.h>

#include <Eigen/Dense>

#include "ActivationFunctions.h"


namespace NeuralNetwork
{
	class SimpleNetwork
	{
	public:
		SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes);
		SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes, float learning_rate);
		~SimpleNetwork();

		float* predict(float* input_data);

		void train(float* input_data, float* output_data);

	private:
		unsigned int _input_nodes;
		unsigned int _hidden_nodes;
		unsigned int _output_nodes;

		Eigen::MatrixXd _weights_ih;
		Eigen::MatrixXd _weights_ho;
		//Utilities::Matrix _weights_ih;
		//Utilities::Matrix _weights_ho;

		Eigen::MatrixXd _bias_h;
		Eigen::MatrixXd _bias_o;
		//Utilities::Matrix _bias_h;
		//Utilities::Matrix _bias_o;

		float _learningRate;
	};
}

#endif // _NN_SIMPLENETWORK_H
