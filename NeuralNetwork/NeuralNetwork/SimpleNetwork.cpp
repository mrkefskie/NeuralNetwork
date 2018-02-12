#include "SimpleNetwork.h"

NeuralNetwork::SimpleNetwork::SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes) :
	_input_nodes(input_nodes), _hidden_nodes(hidden_nodes), _output_nodes(output_nodes)
{
	_weights_ih = Utilities::Matrix(_hidden_nodes, _input_nodes);
	_weights_ho = Utilities::Matrix(_output_nodes, _hidden_nodes);
	_weights_ih.randomize();
	_weights_ho.randomize();


	_bias_h = Utilities::Matrix(_hidden_nodes, 1);
	_bias_o = Utilities::Matrix(_output_nodes, 1);
	_bias_h.randomize();
	_bias_o.randomize();

	_learningRate = 0.1;
}

NeuralNetwork::SimpleNetwork::SimpleNetwork(unsigned int input_nodes, unsigned int hidden_nodes, unsigned int output_nodes, float learning_rate) :
	_input_nodes(input_nodes), _hidden_nodes(hidden_nodes), _output_nodes(output_nodes), _learningRate(learning_rate)
{
	_weights_ih = Utilities::Matrix(_hidden_nodes, _input_nodes);
	_weights_ho = Utilities::Matrix(_output_nodes, _hidden_nodes);
	_weights_ih.randomize();
	_weights_ho.randomize();


	_bias_h = Utilities::Matrix(_hidden_nodes, 1);
	_bias_o = Utilities::Matrix(_output_nodes, 1);
	_bias_h.randomize();
	_bias_o.randomize();
}

NeuralNetwork::SimpleNetwork::~SimpleNetwork()
{
}

float* NeuralNetwork::SimpleNetwork::predict(float* input_data)
{
	Utilities::Matrix inputs = Utilities::Matrix::fromArray(input_data, _input_nodes);

	Utilities::Matrix hidden = _weights_ih * inputs;
	hidden += _bias_h;

	for (unsigned long i = 0; i < hidden.getRows(); i++)
	{
		hidden.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden.getData(i, 0)));
	}


	Utilities::Matrix output = _weights_ho * hidden;
	output += _bias_o;

	for (unsigned long i = 0; i < hidden.getRows(); i++)
	{
		output.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, output.getData(i, 0)));
	}

	return output.toArray();
}

void NeuralNetwork::SimpleNetwork::train(float * input_data, float * output_data)
{
	Utilities::Matrix inputs = Utilities::Matrix::fromArray(input_data, _input_nodes);

	Utilities::Matrix hidden = _weights_ih * inputs;
	hidden += _bias_h;

	for (unsigned long i = 0; i < hidden.getRows(); i++)
	{
		hidden.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden.getData(i, 0)));
	}


	Utilities::Matrix outputs = _weights_ho * hidden;
	outputs += _bias_o;

	for (unsigned long i = 0; i < hidden.getRows(); i++)
	{
		outputs.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, outputs.getData(i, 0)));
	}

	
	Utilities::Matrix targets = Utilities::Matrix::fromArray(output_data, 1);

	Utilities::Matrix output_errors = targets - outputs;

	Utilities::Matrix gradients = outputs;
	for (unsigned long i = 0; i < gradients.getRows(); i++)
	{
		gradients.setData(i, 0, ActivationFunctions::deActivate(SIGMOID_ACTIVATION, outputs.getData(i, 0)));
	}

	gradients = gradients * output_errors;
	gradients = gradients * _learningRate;

	Utilities::Matrix hidden_T = Utilities::Matrix::transpose(inputs);
	Utilities::Matrix weight_ho_deltas = gradients * hidden_T;

	_weights_ho += weight_ho_deltas;
	_bias_o += gradients;


	Utilities::Matrix who_T = Utilities::Matrix::transpose(_weights_ho);
	Utilities::Matrix hidden_errors = who_T * output_errors;

	Utilities::Matrix hidden_gradient = hidden;
	for (unsigned long i = 0; i < gradients.getRows(); i++)
	{
		hidden_gradient.setData(i, 0, ActivationFunctions::deActivate(SIGMOID_ACTIVATION, hidden.getData(i, 0)));
	}

	hidden_gradient = hidden_gradient * hidden_errors;
	hidden_gradient = hidden_gradient * _learningRate;

	Utilities::Matrix inputs_T = Utilities::Matrix::transpose(inputs);
	Utilities::Matrix weights_ih_deltas = hidden_gradient * inputs_T;

	_weights_ih += weights_ih_deltas;
	_bias_h += hidden_gradient;
}
