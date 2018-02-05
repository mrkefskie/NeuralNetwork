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

Utilities::Matrix Utilities::Matrix::add(Utilities::Matrix a, Utilities::Matrix b)
{
	if (a.getCols() != b.getCols())
		throw 1;
	if (a.getRows() != b.getRows())
		throw 2;

	Matrix result(a.getRows(), b.getCols());

	for (unsigned long i = 0; i < result.getRows(); i++)
	{
		for (unsigned long j = 0; j < result.getCols(); j++)
		{
			result.setData(i, j, a.getData(i, j) + b.getData(i, j));
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