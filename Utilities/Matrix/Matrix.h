#ifndef _UTILS_MATRIX_H
#define _UTILS_MATRIX_H

#include <stdlib.h>
#include <random>
#include <time.h>

#include "../Exceptions/MatrixExceptions.h"

namespace Utilities
{
	typedef enum
	{
		ADDITION,
		SUBTRACTION,
		MULTIPLICATION
	} MatrixOperations;

	class Matrix
	{
	public:
		Matrix();
		Matrix(unsigned int rows, unsigned int cols);
		~Matrix();

		static Matrix fromArray(const float* data, unsigned long l);
		float* toArray();

		void randomize();

		
		Matrix operator+(const float n);
		void operator+=(const float n);
		Matrix operator+(Matrix n);
		void operator+=(Matrix n);

		
		Matrix operator-(const float n);
		void operator-=(const float n);
		Matrix operator-(Matrix n);
		void operator-=(Matrix n);


		Matrix operator*(const float n);
		void operator*=(const float n);
		Matrix operator*(Matrix n);
		void operator*=(Matrix n);

		Matrix operator=(Matrix m);



		static Matrix transpose(Matrix m);
		Matrix transpose();
		

		void printToCLI();

		unsigned int getRows() const { return _rows; }
		unsigned int getCols() const { return _cols; }

		float **getData() { return _data; }
		float getData(unsigned int r, unsigned int c) { return _data[r][c]; }
		void setData(unsigned int r, unsigned int c, float data) { _data[r][c] = data; }
	private:
		void add(const float n);
		void add(Matrix n);

		void subtract(const float n);
		void subtract(Matrix n);

		void multiply(const float n);


		bool checkSize(MatrixOperations MO, Matrix a);
		bool checkSize(MatrixOperations MO, Matrix a, Matrix b);

		unsigned int _rows;
		unsigned int _cols;

		float **_data;
	};
}

#endif // _UTILS_MATRIX_H