#ifndef _NN_NODE_H
#define _NN_NODE_H

#include <random>
#include <time.h>

#include "ActivationFunctions.h"

namespace NeuralNetwork
{
	typedef enum
	{
		SIGN
	} ACTIVATION_TYPE;

	/**
	* @brief A class holding a single perceptron
	*
	*/
	class Node
	{
	public:
		/**
		* @brief Constructor, initializes the weights to random
		*
		*/
		Node(unsigned long amountOfInputs, ACTIVATION_TYPE type, float learningRate);
		~Node();

		/**
		* @brief Guess the label of a input
		*
		* @param inputs The input variables
		* @return int The guessed label
		*/
		float guess(float* inputs);

		/**
		* @brief Train this perceptron
		*
		* @param inputs The inputs
		* @param target The required output
		*/
		void train(float* inputs, float target);

		float getWeights(unsigned long i) { return _weights[i]; }

	private:
		/**
		* @brief All the weights used
		*
		*/
		unsigned long _inputs;
		float* _weights;
		float _learningRate;
		ACTIVATION_TYPE _activationType;
	};
}

#endif // _NN_NODE_H
