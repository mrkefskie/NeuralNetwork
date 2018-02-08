#ifndef _UTILS_MATRIXEXCEPTIONS_H
#define _UTILS_MATRIXEXCEPTIONS_H

#include <stdexcept>

namespace Utilities
{
	class matrixException : public std::runtime_error
	{
	public:
		matrixException(char const* const message) throw();
		virtual char const* what() const throw();
	};
}

#endif // _UTILS_MATRIXEXCEPTIONS_H
