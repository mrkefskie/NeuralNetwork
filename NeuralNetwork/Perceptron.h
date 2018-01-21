#pragma once

/**
 * @brief The amount of inputs the perceptron has
 * 
 */
#define AMOUNT_OF_INPUTS 3
/**
 * @brief The learning rate of the perceptron
 * 
 */
#define LEARNING_RATE 0.01

#include <random>
#include <time.h>

/**
 * @brief A class holding a single perceptron
 * 
 */
class Perceptron
{
public:
	/**
	 * @brief Constructor, initializes the weights to random
	 * 
	 */
	Perceptron();
	~Perceptron();

	/**
	 * @brief Guess the label of a input
	 * 
	 * @param inputs The input variables
	 * @return int The guessed label
	 */
	int guess(float inputs[AMOUNT_OF_INPUTS]);

	/**
	 * @brief Train this perceptron
	 * 
	 * @param inputs The inputs
	 * @param target The required output
	 */
	void train(float inputs[AMOUNT_OF_INPUTS], int target);

	/**
	 * @brief All the weights used
	 * 
	 */
	float weights[AMOUNT_OF_INPUTS];
};

