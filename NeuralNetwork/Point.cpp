#include "Point.h"



Network::Point::Point()
{
	//srand(time(NULL));
	x = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
	y = -1.f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1.f - -1.f)));
	bias = 1;

	float lineY = line(x);
	if (y > lineY) label = 1;
	else label = -1;
}

Network::Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
	bias = 1;
}


Network::Point::~Point()
{
}

int Network::Point::pixelX()
{
	int px = (x * (SIZE / 2)) + (SIZE / 2);
	return px;
}

int Network::Point::pixelY()
{
	int py = -(y * (SIZE / 2)) + (SIZE / 2);
	return py;
}

float Network::Point::line(float x)
{
	return 0.8 * x - 0.254;
}

