#include "Point.h"

Data::Point::Point()
{
	_x = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
	_y = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));

	_bias = 1.f;

	float dividing = DivindingLines::WeirdLine(_x);
	if (_y > dividing) _label = 1.f;
	else _label = -1.f;
}

Data::Point::Point(float x, float y) : _x(x), _y(y)
{
	_bias = 1.f;

	float dividing = DivindingLines::WeirdLine(x);
	if (y > dividing) _label = 1.f;
	else _label = -1.f;
}

