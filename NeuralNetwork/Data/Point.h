#ifndef __NN_POINT_H
#define __NN_POINT_H

#include "DividingLines.h"
#include <random>

namespace Data
{
	class Point
	{
	public:
		Point();
		Point(Data::LINE_TYPE type);
		Point(float x, float y);

		float getX() { return _x; }
		float getY() { return _y; }
		float getBias() { return _bias; }

		float getLabel() { return _label; }

		Data::LINE_TYPE getLineType() { return _lineType; }

	private:
		float _x;
		float _y;
		float _bias;
		float _label;

		Data::LINE_TYPE _lineType;
	};
}

#endif // __NN_POINT_H
