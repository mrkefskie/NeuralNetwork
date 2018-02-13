#include "Matrix.h"

Utilities::Matrix::Matrix()
{
	_rows = 0;
	_cols = 0;
	_data = (float**)malloc(sizeof(float*));
	_data[0] = (float*)malloc(sizeof(float*));
	_data[0][0] = -100.f;
}

Utilities::Matrix::Matrix(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols)
{
	_data = (float**)malloc(sizeof(float*) * _rows);


	if (_data == NULL) return;

	for (unsigned long i = 0; i < _rows; i++)
	{
		_data[i] = (float*)malloc(sizeof(float) * _cols);
		if (_data[i] == NULL) return;
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] = 0.f;
		}
	}
}

Utilities::Matrix::~Matrix()
{
}

Utilities::Matrix Utilities::Matrix::fromArray(const float * data, unsigned long l)
{
	Matrix result(l, 1);

	for (unsigned long i = 0; i < l; i++)
	{
		result.setData(i, 0, data[i]);
	}

	return result;
}

float* Utilities::Matrix::toArray()
{
	float* result = (float*)malloc(sizeof(float) * _rows * _cols);

	unsigned long counter = 0;

	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result[counter++] = _data[i][j];
		}
	}

	return result;
}

void Utilities::Matrix::randomize()
{
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] = (rand() / (float)RAND_MAX * 2) - 1.f;
		}
	}
}

/*Utilities::Matrix Utilities::Matrix::operator=(Utilities::Matrix m)
{
	return m + 0;
}*/

#pragma region Addition
void Utilities::Matrix::add(const float n)
{
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] += n;
		}
	}
}

void Utilities::Matrix::add(Utilities::Matrix n)
{
	if (!checkSize(ADDITION, n))
	{
		throw Utilities::matrixException("Matrix exception: ElementWise Addition, matrices do not have the same size.\r\n");
	}

	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] += n.getData(i, j);
		}
	}
}


Utilities::Matrix Utilities::Matrix::operator+(const float n)
{
	Matrix result(_rows, _cols);
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result.setData(i, j, _data[i][j] + n);
		}
	}

	return result;
}

void Utilities::Matrix::operator+=(const float n)
{
	add(n);
}


Utilities::Matrix Utilities::Matrix::operator+(Matrix n)
{
	if (!checkSize(ADDITION, n))
	{
		throw Utilities::matrixException("Matrix exception: ElementWise Addition, matrices do not have the same size.\r\n");
	}

	Matrix result(_rows, _cols);
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result.setData(i, j, _data[i][j] + n.getData(i, j));
		}
	}

	return result;
}

void Utilities::Matrix::operator+=(Matrix n)
{
	if (!checkSize(ADDITION, n))
	{
		throw Utilities::matrixException("Matrix exception: ElementWise Addition, matrices do not have the same size.\r\n");
	}

	add(n);
}
#pragma endregion

#pragma region Subtraction
void Utilities::Matrix::subtract(const float n)
{
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] -= n;
		}
	}
}

void Utilities::Matrix::subtract(Utilities::Matrix n)
{
	if (!checkSize(SUBTRACTION, n))
	{
		throw Utilities::matrixException("Matrix exception: ElementWise Subtraction, matrices do not have the same size.\r\n");
	}

	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] -= n.getData(i, j);
		}
	}

}

Utilities::Matrix Utilities::Matrix::operator-(const float n)
{
	Matrix result(_rows, _cols);
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result.setData(i, j, _data[i][j] - n);
		}
	}

	return result;
}

void Utilities::Matrix::operator-=(const float n)
{
	subtract(n);
}

Utilities::Matrix Utilities::Matrix::operator-(Matrix n)
{
	if (!checkSize(SUBTRACTION, n))
	{
		throw Utilities::matrixException("Matrix exception: ElementWise Subtraction, matrices do not have the same size.\r\n");
	}

	Matrix result(_rows, _cols);
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result.setData(i, j, _data[i][j] - n.getData(i, j));
		}
	}

	return result;
}

void Utilities::Matrix::operator-=(Matrix n)
{
	if (!checkSize(SUBTRACTION, n))
	{
		throw Utilities::matrixException("Matrix exception: ElementWise Addition, matrices do not have the same size.\r\n");
	}

	subtract(n);
}
#pragma endregion

#pragma region Multiplication
void Utilities::Matrix::multiply(const float n)
{
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			_data[i][j] *= n;
		}
	}
}

Utilities::Matrix Utilities::Matrix::operator*(const float n)
{
	Matrix result(_rows, _cols);
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result.setData(i, j, _data[i][j] * n);
		}
	}

	return result;
}

void Utilities::Matrix::operator*=(const float n)
{
	multiply(n);
}

Utilities::Matrix Utilities::Matrix::operator*(Utilities::Matrix n)
{
	if (!checkSize(MULTIPLICATION, n))
	{
		throw Utilities::matrixException("Matrix exception: Multiplication, Matrices cannot be multiplied\r\n");
	}

	Matrix result(_rows, n.getCols());

	for (unsigned long i = 0; i < result.getRows(); i++)
	{
		for (unsigned long j = 0; j < result.getCols(); j++)
		{
			float res = 0.f;
			for (unsigned long k = 0; k < _cols; k++)
			{
				float a = _data[i][k];
				float b = n.getData(k, j);

				res += a * b;
			}
			result.setData(i, j, res);
		}
	}

	return result;
}
#pragma endregion

#pragma region Utilities
Utilities::Matrix Utilities::Matrix::transpose(Utilities::Matrix m)
{
	Utilities::Matrix result(m.getCols(), m.getRows());

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			result.setData(j, i, m.getData(i, j));
		}
	}

	return result;
}

Utilities::Matrix Utilities::Matrix::transpose()
{

	Utilities::Matrix result(_cols, _rows);

	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			result.setData(j, i, _data[i][j]);
		}
	}

	return result;
}

void Utilities::Matrix::printToCLI()
{
	for (unsigned long i = 0; i < _rows; i++)
	{
		for (unsigned long j = 0; j < _cols; j++)
		{
			printf("%f\t", _data[i][j]);
		}
		printf("\r\n");
	}

	printf("\r\n");
}


bool Utilities::Matrix::checkSize(Utilities::MatrixOperations MO, Utilities::Matrix a)
{
	return checkSize(MO, *this, a);
}

bool Utilities::Matrix::checkSize(Utilities::MatrixOperations MO, Utilities::Matrix a, Utilities::Matrix b)
{
	switch (MO)
	{
	case ADDITION:
	case SUBTRACTION:
		if (a.getRows() != b.getRows())
			return false;
		if (a.getCols() != b.getCols())
			return false;
		break;
	case MULTIPLICATION:
		if (a.getCols() != b.getRows())
			return false;
		break;
	default:
		return false;
		break;
	}

	return true;
}
#pragma endregion

