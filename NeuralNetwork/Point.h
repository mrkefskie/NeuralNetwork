#pragma once

/**
 * @brief The size of the 'screen'
 * 
 */
#define SIZE 20

#include <time.h>
#include <random>

class Point
{
public:
	/**
	 * @brief Initializes the point with a random X and Y.
	 * 
	 */
	Point();
	~Point();

	/**
	 * @brief The X value
	 * 
	 */
	int x;
	/**
	 * @brief The Y value
	 * 
	 */
	int y;
	/**
	 * @brief The label it got with the X and Y
	 * 
	 */
	int label;
};

