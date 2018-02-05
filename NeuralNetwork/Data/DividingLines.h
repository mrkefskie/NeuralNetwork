#ifndef __DIVIDINGLINES_H
#define __DIVIDINGLINES_H

#include <math.h>

namespace Data
{
	typedef enum
	{
		STRAIGHT,
		PARABOLIC,
		SQRT
	} LINE_TYPE;

	class DivindingLines
	{
	public:
		static float straightLine(float x);
		static float Parabolic(float x);
		static float squareRoot(float x);
	};
}

#endif // __DIVIDINGLINES_H
