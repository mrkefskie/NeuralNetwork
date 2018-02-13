#include "SimpleNetwork.h"

#define DEBUG

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

	Utilities::Matrix hidden_inputs = _weights_ih * inputs;
	Utilities::Matrix hidden_outputs(hidden_inputs.getRows(), hidden_inputs.getCols());

	for (unsigned long i = 0; i < hidden_inputs.getRows(); i++)
	{
		hidden_outputs.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden_inputs.getData(i, 0)));
	}

	Utilities::Matrix final_inputs = _weights_ho * hidden_outputs;
	Utilities::Matrix final_outputs(final_inputs.getRows(), final_inputs.getCols());

	for (unsigned long i = 0; i < final_inputs.getRows(); i++)
	{
		final_outputs.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, final_inputs.getData(i, 0)));
	}

	return final_outputs.toArray();
}

void NeuralNetwork::SimpleNetwork::train(float * input_data, float * output_data)
{
	Utilities::Matrix inputs = Utilities::Matrix::fromArray(input_data, _input_nodes);
	Utilities::Matrix targets = Utilities::Matrix::fromArray(output_data, _output_nodes);

	Utilities::Matrix hidden_inputs = _weights_ih * inputs;
	Utilities::Matrix hidden_outputs(hidden_inputs.getRows(), hidden_inputs.getCols());

	for (unsigned long i = 0; i < hidden_inputs.getRows(); i++)
	{
		hidden_outputs.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden_inputs.getData(i, 0)));
	}

	Utilities::Matrix final_inputs = _weights_ho * hidden_outputs;
	Utilities::Matrix final_outputs(final_inputs.getRows(), final_inputs.getCols());

	for (unsigned long i = 0; i < final_inputs.getRows(); i++)
	{
		final_outputs.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, final_inputs.getData(i, 0)));
	}

	// Output layer error is the (target - actual)
	Utilities::Matrix output_errors = targets - final_outputs;

	// Hidden layer error is the output_errors, split by weights, recombined at hidden nodes
	Utilities::Matrix hidden_errors = _weights_ho.transpose() * output_errors;

	// Update the weights for the links between the hidden and output layers
	Utilities::Matrix final_outputs_back(final_outputs.getRows(), final_outputs.getCols());
	for (unsigned long i = 0; i < final_outputs_back.getRows(); i++)
	{
		final_outputs_back.setData(i, 0, ActivationFunctions::deActivate(SIGMOID_ACTIVATION, final_outputs.getData(i, 0)));
	}

	Utilities::Matrix tmp = output_errors * final_outputs_back;
	tmp = tmp * _learningRate;
	_weights_ho = _weights_ho + tmp;

	



	/*// Generate the hidden outputs
	Utilities::Matrix inputs = Utilities::Matrix::fromArray(input_data, _input_nodes);

	Utilities::Matrix hidden = _weights_ih * inputs;
	hidden += _bias_h+0;
	// Activation Functions
	for (unsigned long i = 0; i < hidden.getRows(); i++)
	{
		hidden.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, hidden.getData(i, 0)));
	}

	// Geneate the output's output
	Utilities::Matrix outputs = _weights_ho * hidden;
	outputs += _bias_o;
	// Activation Functions
	for (unsigned long i = 0; i < outputs.getRows(); i++)
	{
		outputs.setData(i, 0, ActivationFunctions::activate(SIGMOID_ACTIVATION, outputs.getData(i, 0)));
	}

	// Convert array to Matrix
	Utilities::Matrix targets = Utilities::Matrix::fromArray(output_data, 1);


	// Calculate the errors (targets-outputs)
	Utilities::Matrix output_errors = targets - outputs;

	// Deactivation (x = y * (1 - y))
	Utilities::Matrix gradients = outputs+0;
	for (unsigned long i = 0; i < gradients.getRows(); i++)
	{
		gradients.setData(i, 0, ActivationFunctions::deActivate(SIGMOID_ACTIVATION, gradients.getData(i, 0)));
	}

	// Calculate gradients
	gradients = gradients * output_errors;
	gradients = gradients * _learningRate;

	// Calculate deltas
	Utilities::Matrix hidden_T = hidden.transpose();
	Utilities::Matrix weight_ho_deltas = gradients * hidden_T;

	// Adjust weights by deltas
	_weights_ho += weight_ho_deltas;
	// Adjust bias by its deltas (gradient)
	_bias_o += gradients;


	// Calculate the hidden layer error
	Utilities::Matrix who_T = _weights_ho.transpose();
	Utilities::Matrix hidden_errors = (who_T * output_errors).transpose();

	// Calculate hidden gradient
	Utilities::Matrix hidden_gradient = hidden+0;
	for (unsigned long i = 0; i < hidden_gradient.getRows(); i++)
	{
		hidden_gradient.setData(i, 0, ActivationFunctions::deActivate(SIGMOID_ACTIVATION, hidden_gradient.getData(i, 0)));
	}

	hidden_gradient = hidden_gradient * hidden_errors;
	hidden_gradient = hidden_gradient * _learningRate;

	// Calculate input->hidden deltas
	Utilities::Matrix inputs_T = inputs + 0;// .transpose();
	Utilities::Matrix weights_ih_deltas = hidden_gradient * inputs_T;

	_weights_ih += hidden_gradient;// weights_ih_deltas;
	_bias_h += weights_ih_deltas;// hidden_gradient;*/
}
