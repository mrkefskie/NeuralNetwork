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

	int pixelX();
	int pixelY();

	float line(float x);

	/**
	 * @brief The X value
	 * 
	 */
	float x;
	/**
	 * @brief The Y value
	 * 
	 */
	float y;
	/**
	* @brief The bias value
	*
	*/
	float bias;

	/**
	 * @brief The label it got with the X and Y
	 * 
	 */
	int label;
};

