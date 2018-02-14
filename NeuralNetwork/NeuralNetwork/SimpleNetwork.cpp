#include "SimpleNetwork.h"

#include <time.h>
#include <iostream>

NeuralNetwork::SimpleNetwork::SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes) :
	_input_nodes(input_nodes), _hidden_nodes(hidden_nodes), _output_nodes(output_nodes)
{
	srand(time(NULL));

	// Initialize weights random
	_weights_ih = Eigen::MatrixXd::Random(_hidden_nodes, _input_nodes);
	_weights_ho = Eigen::MatrixXd::Random(_output_nodes, _hidden_nodes);

	// Initialize biases random (NOT USED YET)
	_bias_h = Eigen::MatrixXd::Random(_hidden_nodes, 1);
	_bias_o = Eigen::MatrixXd::Random(_output_nodes, 1);

	_learningRate = 0.1;
}

NeuralNetwork::SimpleNetwork::SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes, float learning_rate) :
	_input_nodes(input_nodes), _hidden_nodes(hidden_nodes), _output_nodes(output_nodes), _learningRate(learning_rate)
{
	srand(time(NULL));

	// Initialize weights random
	_weights_ih = Eigen::MatrixXd::Random(_hidden_nodes, _input_nodes);
	_weights_ho = Eigen::MatrixXd::Random(_output_nodes, _hidden_nodes);

	// Initialize biases random (NOT USED YET)
	_bias_h = Eigen::MatrixXd::Random(_hidden_nodes, 1);
	_bias_o = Eigen::MatrixXd::Random(_output_nodes, 1);
}

NeuralNetwork::SimpleNetwork::~SimpleNetwork()
{
}

float* NeuralNetwork::SimpleNetwork::predict(float* input_data)
{
	// Convert inputs to matrix
	Eigen::MatrixXd inputs(_input_nodes, 1);
	for (size_t i = 0; i < _input_nodes; i++)
	{
		inputs(i, 0) = input_data[i];
	}

	// Calculate the hidden output
	Eigen::MatrixXd hidden = _weights_ih * inputs;
	hidden = ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden);

	// Calculate the final outputs
	Eigen::MatrixXd outputs = _weights_ho * hidden;
	outputs = ActivationFunctions::activate(SIGMOID_ACTIVATION, outputs);

	// Create an array to hold the outputs
	float* ret = (float*)malloc(sizeof(float) * outputs.rows());

	// Copy the data to the array
	for (size_t i = 0; i < outputs.rows(); i++)
	{
		ret[i] = (float)outputs.data()[i];
	}

	return ret; // Return the array
}

void NeuralNetwork::SimpleNetwork::train(float * input_data, float * output_data)
{
	// Convert inputs to matrix
	Eigen::MatrixXd inputs(_input_nodes, 1);
	for (size_t i = 0; i < _input_nodes; i++)
	{
		inputs(i, 0) = input_data[i];
	}
	//std::cout << std::endl << "inputs:" << std::endl << inputs << std::endl;

	// Convert targets to matrix
	Eigen::MatrixXd targets(_output_nodes, 1);
	for (size_t i = 0; i < _output_nodes; i++)
	{
		targets(i, 0) = output_data[i];
	}
	//std::cout << std::endl << "targets:" << std::endl << targets << std::endl;

	// Calculate the hidden layer
	Eigen::MatrixXd hidden_inputs = _weights_ih * inputs;

	Eigen::MatrixXd hidden_outputs = ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden_inputs);

	// Calculate the final output layer
	Eigen::MatrixXd final_inputs = _weights_ho * hidden_outputs;

	Eigen::MatrixXd final_outputs = ActivationFunctions::activate(SIGMOID_ACTIVATION, final_inputs);

	// Output layer error is target - actual
	Eigen::MatrixXd output_errors = targets - final_outputs;

	// Hidden layer error is the output_errors, split by weights, recombined at hidden nodes
	Eigen::MatrixXd hidden_errors = _weights_ho.transpose() * output_errors;

	// Update the weights for the links between the hidden and output layers
	Eigen::MatrixXd deActivate_outputs = ActivationFunctions::deActivate(SIGMOID_ACTIVATION, final_outputs);
	_weights_ho += _learningRate * (output_errors * deActivate_outputs * hidden_outputs.transpose());

	// Update the weights for the links between the input and hidden layers
	Eigen::MatrixXd deActivate_hidden = ActivationFunctions::deActivate(SIGMOID_ACTIVATION, hidden_outputs);
	_weights_ih += _learningRate * (hidden_errors.cwiseProduct(deActivate_hidden) * inputs.transpose());
}
