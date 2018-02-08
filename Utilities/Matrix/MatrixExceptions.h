#ifndef _UTILS_MATRIXEXCEPTIONS_H
#define _UTILS_MATRIXEXCEPTIONS_H

#include <exception>

namespace Utilities
{
	class a : public std::exception
	{
		virtual const char* what() const throw()
		{
			return "";
		}
	} matrixNotTheSameSizeException;
}

#endif // _UTILS_MATRIXEXCEPTIONS_H
