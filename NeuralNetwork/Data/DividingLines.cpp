#include "DividingLines.h"

float Data::DivindingLines::straightLine(float x)
{
	return 0.8f*x - 0.254;
}

float Data::DivindingLines::WeirdLine(float x)
{
	return x * x + x;
}
