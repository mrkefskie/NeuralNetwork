#include "Point.h"



Point::Point()
{
	//srand(time(NULL));
	x = rand() % (SIZE - 0 + 1) + 0;
	y = rand() % (SIZE - 0 + 1) + 0;

	if (x > y) label = 1;
	else label = -1;
}


Point::~Point()
{
}
