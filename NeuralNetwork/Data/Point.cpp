#include "Point.h"

Data::Point::Point()
{
	_x = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
	_y = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));

	_bias = 1.f;

	_lineType = STRAIGHT;

	float dividing = DivindingLines::straightLine(_x);
	if (_y > dividing) _label = 1.f;
	else _label = -1.f;
}

Data::Point::Point(Data::LINE_TYPE type) : _lineType(type)
{
	_x = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
	_y = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));

	_bias = 1.f;

	float dividing = 0.f;

	switch (_lineType)
	{
	case STRAIGHT:
		dividing = DivindingLines::straightLine(_x);
		break;
	case PARABOLIC:
		dividing = DivindingLines::Parabolic(_x);
		break;
	default:
		dividing = DivindingLines::straightLine(_x);
		break;
	}

	if (_y > dividing) _label = 1.f;
	else _label = -1.f;
}

Data::Point::Point(float x, float y) : _x(x), _y(y)
{
	_bias = 1.f;

	_lineType = STRAIGHT;

	float dividing = DivindingLines::straightLine(x);
	if (y > dividing) _label = 1.f;
	else _label = -1.f;
}

