#include "Matriz.h"
#include <math.h>
#include <iostream>

Matriz::Matriz() {
	cols = 3;
	rows = 3;
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, 0);
		mat[i][i] = 1;
	}

}

Matriz::Matriz(const Matriz& other)
{
	mat = other.mat;
	rows = other.rows;
	cols = other.cols;
}


Matriz Matriz::Inversa()
{
	Matriz m, n, o;
	float num = 0, mod = 0;
	m = mat;

	try
	{
		for (int j = 0; j < cols; j++)
		{
			for (int i = 0; i < rows; i++)
			{
				if (m(i, j) != 0)
				{
					if (i == j)
					{
						mod = m(i, j);
						for (int k = 0; k < cols; k++)
						{
							m(i, k) *= 1/mod;

							n(i, k) *= 1 / mod;
						}
					}
					else
					{
						mod = m(i, j) / m(j, j);
						for (int k = 0; k < cols; k++)
						{
							m(i, k) = m(i, k) - (m(j, k) * mod);
							n(i, k) = n(i, k) - (n(j, k) * mod);
						}
					}
				}
				
			}
		}
		if (m == o)
		{
			std::cout << "Se completo" << std::endl; 
		}
		else
		{
			m.Print();
			std::cout << std::endl;
		}
	}
	catch (...)
	{
		std::cout << "Creo que dividimos entre 0 :v" << std::endl;
	}

	
	return n;
}

std::vector<float> SumVector(std::vector<float>, std::vector<float>);

Matriz::Matriz(unsigned rows, unsigned cols)
{
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, i);
	}
	
	this->rows = rows;
	this->cols = cols;
}

Matriz::Matriz(unsigned rows, unsigned cols, int n)
{
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, i * n);
	}

	this->rows = rows;
	this->cols = cols;
}

Matriz& Matriz::operator=(Matriz other)
{
	if (&other == this)
		return *this;

	unsigned new_rows = other.GetRows();
	unsigned new_cols = other.GetCols();

	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols);
		for (int j = 0; j < mat[i].size(); j++)
		{
			mat[i][j] = other(i, j);
		}
	}
	return *this;
}

bool Matriz::operator==(Matriz other)
{
	if (&other == this)
		return true;

	if (cols != other.GetCols() && rows != other.GetRows())
	{
		return false;
	}

	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[i].size(); j++)
		{
			if (mat[i][j] != other(i, j))
			{
				return false;
			}
		}
	}
	return true;
}

Matriz& Matriz::operator=(std::vector<std::vector<float>> v)
{
	
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mat[i][j] = v[i][j];
		}
	}
	return *this;
}

Matriz Matriz::operator+(Matriz& other)
{
	Matriz m(rows, cols, 0);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m(i, j) = mat[i][j] + other(i, j);
		}
	}

	return m;
}

Matriz Matriz::operator-(Matriz& other)
{
	Matriz m(rows, cols, 0);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m(i, j) = mat[i][j] - other(i, j);
		}
	}

	return m;
}

Matriz Matriz::operator* (Matriz& other) 
{
	Matriz m(rows, cols, 0);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m(i, j) = mat[i][0] * other(0, j);
			m(i, j) += mat[i][1] * other(1, j);
			m(i, j) += mat[i][2] * other(2, j);
		}
	}

	return m;
}

void Matriz::Transpose()
{
	std::vector<std::vector<float>>m;

	m = mat;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			mat[i][j] = m[j][i];
		}
	}
	
}

Matriz Matriz::operator+(float num)
{
	Matriz m(rows, cols, 0);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m(i, j) = mat[i][j] + num;
		}
	}
	return m;
}

Matriz Matriz::operator-(float num)
{
	Matriz m(rows, cols, 0);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m(i, j) = mat[i][j] - num;
		}
	}
	return m;
}

Matriz Matriz::operator*(float num)
{
	Matriz m(rows, cols, 0);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			m(i, j) = mat[i][j] * num;
		}
	}
	return m;
}



float& Matriz::operator()(unsigned y, unsigned x)
{
	return mat[y][x];
}

unsigned Matriz::GetRows()
{
	return rows;
}

unsigned Matriz::GetCols()
{
	return cols;
}

void Matriz::Print()
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			std::cout << mat[i][j] << "  ";
		}
		std::cout << std::endl;
	}
}

Matriz::~Matriz()
{

}