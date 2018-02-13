#include "SimpleNetwork.h"

#include <iostream>

#define DEBUG

NeuralNetwork::SimpleNetwork::SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes) :
	_input_nodes(input_nodes), _hidden_nodes(hidden_nodes), _output_nodes(output_nodes)
{
	_weights_ih = Eigen::MatrixXd::Random(_hidden_nodes, _input_nodes);
	_weights_ho = Eigen::MatrixXd::Random(_output_nodes, _hidden_nodes);

	_bias_h = Eigen::MatrixXd::Random(_hidden_nodes, 1);
	_bias_o = Eigen::MatrixXd::Random(_output_nodes, 1);

	/*_weights_ih = Utilities::Matrix(_hidden_nodes, _input_nodes);
	_weights_ho = Utilities::Matrix(_output_nodes, _hidden_nodes);
	_weights_ih.randomize();
	_weights_ho.randomize();


	_bias_h = Utilities::Matrix(_hidden_nodes, 1);
	_bias_o = Utilities::Matrix(_output_nodes, 1);
	_bias_h.randomize();
	_bias_o.randomize();*/

	_learningRate = 0.1;
}

NeuralNetwork::SimpleNetwork::SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes, float learning_rate) :
	_input_nodes(input_nodes), _hidden_nodes(hidden_nodes), _output_nodes(output_nodes), _learningRate(learning_rate)
{
	_weights_ih = Eigen::MatrixXd::Random(_hidden_nodes, _input_nodes);
	_weights_ho = Eigen::MatrixXd::Random(_output_nodes, _hidden_nodes);

	_bias_h = Eigen::MatrixXd::Random(_hidden_nodes, 1);
	_bias_o = Eigen::MatrixXd::Random(_output_nodes, 1);

	/*_weights_ih = Utilities::Matrix(_hidden_nodes, _input_nodes);
	_weights_ho = Utilities::Matrix(_output_nodes, _hidden_nodes);
	_weights_ih.randomize();
	_weights_ho.randomize();


	_bias_h = Utilities::Matrix(_hidden_nodes, 1);
	_bias_o = Utilities::Matrix(_output_nodes, 1);
	_bias_h.randomize();
	_bias_o.randomize();*/
}

NeuralNetwork::SimpleNetwork::~SimpleNetwork()
{
}

float* NeuralNetwork::SimpleNetwork::predict(float* input_data)
{
	Eigen::MatrixXd inputs(_input_nodes, 1);
	for (size_t i = 0; i < _input_nodes; i++)
	{
		inputs(i, 0) = input_data[i];
	}

	Eigen::MatrixXd hidden = _weights_ih * inputs;

	hidden = ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden);

	Eigen::MatrixXd outputs = _weights_ho * hidden;

	outputs = ActivationFunctions::activate(SIGMOID_ACTIVATION, outputs);

	float* ret = (float*)malloc(sizeof(float) * outputs.rows());

	for (size_t i = 0; i < outputs.rows(); i++)
	{
		ret[i] = (float)outputs.data()[i];
	}

	return ret;
}

void NeuralNetwork::SimpleNetwork::train(float * input_data, float * output_data)
{
	// Convert inputs to matrix
	Eigen::MatrixXd inputs(_input_nodes, 1);
	for (size_t i = 0; i < _input_nodes; i++)
	{
		inputs(i, 0) = input_data[i];
	}

	// Convert targets to matrix
	Eigen::MatrixXd targets(_output_nodes, 1);
	for (size_t i = 0; i < _output_nodes; i++)
	{
		targets(i, 0) = output_data[i];
	}

	// Calculate the hidden layer
	Eigen::MatrixXd hidden = _weights_ih * inputs;
	hidden = ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden);

	// Calculate the output layer
	Eigen::MatrixXd outputs = _weights_ho * hidden;
	outputs = ActivationFunctions::activate(SIGMOID_ACTIVATION, outputs);

	// Calculate the output errors
	Eigen::MatrixXd output_errors = targets - outputs;
	// Calculate the hidden errors
	Eigen::MatrixXd hidden_errors = _weights_ho.transpose() * output_errors;

	// Update the weights for the links between the hidden and output layers
	Eigen::MatrixXd deActivate = ActivationFunctions::deActivate(SIGMOID_ACTIVATION, outputs);
	_weights_ho += _learningRate * (output_errors * deActivate * hidden.transpose());

	std::cout << std::endl << "HIDDEN:" << std::endl << hidden << std::endl;

	// Update the weights for the links between the input and hidden layers
	Eigen::MatrixXd deActivate1 = ActivationFunctions::deActivate(SIGMOID_ACTIVATION, hidden);

	std::cout << std::endl << "DEACTIVATE:" << std::endl << deActivate1 << std::endl;

	Eigen::MatrixXd tmp = hidden_errors * deActivate1.transpose();

	std::cout << std::endl << "HIDDEN_ERRORS * DEACTIVATE:" << std::endl << tmp << std::endl;

	tmp *= inputs;
	std::cout << std::endl << "TMP * INPUTS:" << std::endl << tmp << std::endl;
	tmp = tmp * _learningRate;
	std::cout << std::endl << "TMP * LEARNINGRATE:" << std::endl << tmp << std::endl;

	_weights_ih = _weights_ih + tmp;
}
