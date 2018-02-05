#ifndef _UTILS_MATRIX_H
#define _UTILS_MATRIX_H

#include <stdlib.h>
#include <random>
#include <time.h>

namespace Utilities
{
	class Matrix
	{
	public:
		Matrix();
		Matrix(unsigned int rows, unsigned int cols);
		~Matrix();

		void randomize();

		void add(const float n);
		void add(Matrix n);

		static Matrix add(Matrix a, Matrix b);

		

		void printToCLI();


		unsigned int getRows() const { return _rows; }
		unsigned int getCols() const { return _cols; }

		float **getData() { return _data; }
		float getData(unsigned int r, unsigned int c) { return _data[r][c]; }
		void setData(unsigned int r, unsigned int c, float data) { _data[r][c] = data; }
	private:
		unsigned int _rows;
		unsigned int _cols;

		float **_data;
	};
}

#endif // _UTILS_MATRIX_H