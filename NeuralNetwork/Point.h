#pragma once

#include <time.h>
#include <random>

#include "Defines.h"

namespace Network
{
	class Point
	{
	public:
		/**
		 * @brief Initializes the point with a random X and Y.
		 *
		 */
		Point();
		Point(float x, float y);
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
}
