#include "MatrixExceptions.h"

Utilities::matrixException::matrixException(char const * const message) throw() : std::runtime_error(message)
{
	/*char* header = (char*)"Matrix Exception: ";
	size_t size1 = strlen(header);
	size_t size2 = strlen(message);
	size_t size = size1 + size2;
	char* result = (char*)malloc(sizeof(char) * size);
	sprintf_s(result, size + strlen(header), "%s%s", header, message);
	std::runtime_error((const char*)result);*/
}

char const * Utilities::matrixException::what() const throw()
{
	return exception::what();
}
