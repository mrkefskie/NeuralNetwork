#include "Matrix.h"

Utilities::Matrix::Matrix()
{}

Utilities::Matrix::Matrix(unsigned int rows, unsigned int cols) : _rows(rows), _cols(cols)
{
	_data = (float**)malloc(sizeof(float*) * _rows);


	if (_data == NULL) throw "Memmory allocation did not work!";

	for (unsigned long i = 0; i < _rows; i++)
	{
		_data[i] = (float*)malloc(sizeof(float) * _cols);
		if (_data[i] == NULL) throw "Memmory allocation did not work!";
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
		throw 1;

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
	add(n);
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
