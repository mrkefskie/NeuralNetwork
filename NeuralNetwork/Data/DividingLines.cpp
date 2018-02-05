#include "DividingLines.h"

float Data::DivindingLines::straightLine(float x)
{
	return 0.8f*x - 0.254;
}

float Data::DivindingLines::Parabolic(float x)
{
	return x * x + x;
}

float Data::DivindingLines::squareRoot(float x)
{
	return 0.5f*sqrt(x + 1.f);
}
