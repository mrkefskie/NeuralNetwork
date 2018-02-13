#include "pch.h"
#include "../Utilities/Matrix/Matrix.h"


TEST(MATRIX, AddScalarToMatrix) {
	Utilities::Matrix m(3, 2);

	float data = 0.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			m.setData(i, j, data++);
		}
	}

	Utilities::Matrix r = m + 1.f;
	data = 1.f;

	for (unsigned long i = 0; i < r.getRows(); i++)
	{
		for (unsigned long j = 0; j < r.getCols(); j++)
		{
			EXPECT_FLOAT_EQ(data - 1, m.getData(i, j));
			EXPECT_FLOAT_EQ(data++, r.getData(i, j));
		}
	}
}

TEST(MATRIX, AddMatrixToMatrix)
{
	Utilities::Matrix m(2, 2);
	Utilities::Matrix n(2, 2);

	float d1 = 1.f;
	float d2 = 10.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			m.setData(i, j, d1++);
			n.setData(i, j, d2++);
		}
	}

	Utilities::Matrix r = m + n;

	d1 = 1.f;
	d2 = 10.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			EXPECT_FLOAT_EQ(d1++, m.getData(i, j));
			EXPECT_FLOAT_EQ(d2++, n.getData(i, j));
		}
	}

	EXPECT_FLOAT_EQ(11.f, r.getData(0, 0));
	EXPECT_FLOAT_EQ(13.f, r.getData(0, 1));
	EXPECT_FLOAT_EQ(15.f, r.getData(1, 0));
	EXPECT_FLOAT_EQ(17.f, r.getData(1, 1));
}

TEST(MATRIX, SubtractScalarFromMatix)
{
	Utilities::Matrix m(3, 2);

	float data = 10.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			m.setData(i, j, data++);
		}
	}

	m -= 1.f;
	data = 9.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			EXPECT_FLOAT_EQ(data++, m.getData(i, j));
		}
	}

}

TEST(MATRIX, SubtractMatrixFromMatrix)
{
	Utilities::Matrix m(2, 2);
	Utilities::Matrix n(2, 2);

	float d1 = 1.f;
	float d2 = 10.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			n.setData(i, j, d1++);
			m.setData(i, j, d2++);
		}
	}

	m -= n;

	EXPECT_FLOAT_EQ(9.f, m.getData(0, 0));
	EXPECT_FLOAT_EQ(9.f, m.getData(0, 1));
	EXPECT_FLOAT_EQ(9.f, m.getData(1, 0));
	EXPECT_FLOAT_EQ(9.f, m.getData(1, 1));
}

TEST(MATRIX, MultiplyScalarWithMatrix)
{
	Utilities::Matrix m(3, 2);

	float data = 9.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			m.setData(i, j, data++);
		}
	}

	float mult = 2.f;

	Utilities::Matrix n;
	n = m * mult;
	data = 9.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			ASSERT_FLOAT_EQ(data, m.getData(i, j));
			ASSERT_FLOAT_EQ(data*mult, n.getData(i, j));
			data++;
		}
	}
}

TEST(MATRIX, MultiplyMatrixWithMatrix)
{
	Utilities::Matrix m(10, 7);
	Utilities::Matrix n(7, 15);

	float d1 = 1.f;
	float d2 = 7.f;

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		for (unsigned long j = 0; j < m.getCols(); j++)
		{
			m.setData(i, j, d1++);
		}
	}
	for (unsigned long i = 0; i < n.getRows(); i++)
	{
		for (unsigned long j = 0; j < n.getCols(); j++)
		{
			n.setData(i, j, d2++);
		}
	}

	Utilities::Matrix expected(10, 15);
	for (unsigned long i = 0; i < expected.getRows(); i++)
	{
		for (unsigned long j = 0; j < expected.getCols(); j++)
		{
			float sum = 0;
			for (unsigned long k = 0; k < m.getCols(); k++)
			{
				sum += m.getData(i, k) * n.getData(k, j);
			}
			expected.setData(i, j, sum);
		}
	}

	m.printToCLI();
	n.printToCLI();

	Utilities::Matrix r = m * n;

	r.printToCLI();

	ASSERT_EQ(expected.getRows(), r.getRows());
	ASSERT_EQ(expected.getCols(), r.getCols());


	for (unsigned long i = 0; i < n.getRows(); i++)
	{
		for (unsigned long j = 0; j < n.getCols(); j++)
		{
			ASSERT_FLOAT_EQ(expected.getData(i, j), r.getData(i, j));
		}
	}
}

TEST(MATRIX, TransposeMatrixCheckForSize)
{
	srand(time(NULL));

	int rows = rand() % (1000 - 10 + 1) + 10;
	int cols = rand() % (1000 - 10 + 1) + 10;

	Utilities::Matrix m(rows, cols);
	m.randomize();

	Utilities::Matrix m_T = m.transpose();


	ASSERT_EQ(cols, m_T.getRows());
	ASSERT_EQ(rows, m_T.getCols());
}

TEST(MATRIX, TransposeMatrixCheckForValues)
{
	int size = rand() % (1000 - 10 + 1) + 10;

	Utilities::Matrix m(size, size);
	m.randomize();

	Utilities::Matrix m_T = m.transpose();

	ASSERT_EQ(size, m_T.getRows());
	ASSERT_EQ(size, m_T.getCols());

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			ASSERT_FLOAT_EQ(m.getData(i, j), m_T.getData(j, i));
		}
	}
}

TEST(MATRIX, CopyMatrix)
{
	Utilities::Matrix org(2, 2);
	org.setData(0, 0, 0);
	org.setData(0, 1, 1);
	org.setData(1, 0, 2);
	org.setData(1, 1, 3);

	org.printToCLI();

	Utilities::Matrix cpy = org+0;
	cpy.setData(0, 0, 10);

	org.printToCLI();
	cpy.printToCLI();

	ASSERT_FLOAT_EQ(0.f, org.getData(0, 0));
}


TEST(MATRIX, FromArray)
{
	unsigned long l = 5;
	float* data = (float*)malloc(sizeof(float) * l);

	for (unsigned long i = 0; i < l; i++)
	{
		data[i] = (i * 10.f) + 3.f;
	}

	Utilities::Matrix m = Utilities::Matrix::fromArray(data, l);

	ASSERT_EQ(l, m.getRows());

	for (unsigned long i = 0; i < l; i++)
	{
		ASSERT_FLOAT_EQ((i * 10.f) + 3.f, m.getData(i, 0));
	}
}

TEST(MATRIX, ToArray)
{
	unsigned long l = 6;

	Utilities::Matrix m(l, 1);

	for (unsigned long i = 0; i < m.getRows(); i++)
	{
		m.setData(i, 0, (i * 10.f) + 3.f);
	}

	float* data = m.toArray();

	for (unsigned long i = 0; i < l; i++)
	{
		ASSERT_FLOAT_EQ((i * 10.f) + 3.f, m.getData(i, 0));
	}

}