#ifndef __DATA_H
#define __DATA_H

namespace Data
{
	typedef struct
	{
		unsigned long input_length;
		unsigned long output_length;

		float* inputs;
		float* outputs;
	} DATA_TYPE;
}

#endif // __DATA_H
