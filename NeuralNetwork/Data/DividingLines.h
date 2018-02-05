#ifndef __DIVIDINGLINES_H
#define __DIVIDINGLINES_H

namespace Data
{
	typedef enum
	{
		STRAIGHT,
		PARABOLIC
	} LINE_TYPE;

	class DivindingLines
	{
	public:
		static float straightLine(float x);
		static float Parabolic(float x);
	};
}

#endif // __DIVIDINGLINES_H
