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




#pragma region Utilities
Utilities::Matrix Utilities::Matrix::transpose(Utilities::Matrix m)
{
	Utilities::Matrix result(m.getCols(), m.getRows());

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getRows(); j++)
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
		if (a.getRows() != b.getRows())
			return false;
		if (a.getCols() != b.getCols())
			return false;
		break;
	case MULTIPLICATION:
		break;
	default:
		return false;
		break;
	}

	return true;
}
#pragma endregion

