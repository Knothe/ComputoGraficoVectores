#include "Matriz.h"
#include <math.h>
#include <iostream>
//
//Matriz::Matriz(char t, float x, float y)
//{
//	m = new float* [3];
//	for (int i = 0; i < 3; i++)
//	{
//		m[i] = new float[3];
//	}
//	
//	switch (t)
//	{
//	case 'r':
//		std::cout << cos(x) << "   " << sin(x) << std::endl;
//		m[0][0] = cos(x);
//		m[0][1] = sin(x);
//		m[0][2] = 0;
//		m[1][0] = -sin(x);
//		m[1][1] = cos(x);
//		m[1][2] = 0;
//		m[2][0] = 0;
//		m[2][1] = 0;
//		m[2][2] = 1;
//		break;
//	case 't':
//		m[0][0] = 1;
//		m[0][1] = 0;
//		m[0][2] = 0;
//		m[1][0] = 0;
//		m[1][1] = 1;
//		m[1][2] = 0;
//		m[2][0] = x;
//		m[2][1] = y;
//		m[2][2] = 1;
//		break;
//	case 'e':
//		m[0][0] = x;
//		m[0][1] = 0;
//		m[0][2] = 0;
//		m[1][0] = 0;
//		m[1][1] = y;
//		m[1][2] = 0;
//		m[2][0] = 0;
//		m[2][1] = 0;
//		m[2][2] = 1;
//		break;
//	case 'n':
//		m[0][0] = 0;
//		m[0][1] = 0;
//		m[0][2] = 0;
//		m[1][0] = 0;
//		m[1][1] = 0;
//		m[1][2] = 0;
//		m[2][0] = 0;
//		m[2][1] = 0;
//		m[2][2] = 0;
//		break;
//	}
//	
//}
//
//Matriz::Matriz()
//{
//	m = new float* [3];
//	for (int i = 0; i < 3; i++)
//	{
//		m[i] = new float[3];
//	}
//
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			m[j][i] = 0;
//		}
//	}
//}
//
//void Matriz::PrintMatriz()
//{
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			std::cout<<m[i][j]<< " ";
//		}
//		std::cout << std::endl;
//	}
//}
//
//float Matriz::GetValue(int x, int y)
//{
//	return m[x][y];
//}
//
//void Matriz::SetValue(int x, int y, float value)
//{
//	m[x][y] = value;
//}
//
//Matriz Matriz::operator+(Matriz other)
//{
//	Matriz temp('n', 0, 0);
//
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			temp.SetValue(j, i, m[j][i] + other.GetValue(j, i));
//		}
//	}
//
//	return temp;
//}
//
//Matriz Matriz::operator-(Matriz other)
//{
//	Matriz temp('n', 0, 0);
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			temp.SetValue(j, i, m[j][i] - other.GetValue(j, i));
//		}
//	}
//	return temp;
//}
//
//Matriz Matriz::operator*(Matriz other)
//{
//	Matriz temp;
//	float value;
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			value = m[j][0] * other.GetValue(0,i);
//			value += m[j][1] * other.GetValue(1, i);
//			value += m[j][2] * other.GetValue(2, i);
//			temp.SetValue(j, i, value);
//
//		}
//	}
//	return temp;
//}
//
//void Matriz::operator=(Matriz other)
//{
//	for (int i = 0; i < 3; i++)
//	{
//		for (int j = 0; j < 3; j++)
//		{
//			m[j][i] = other.GetValue(j, i);
//		}
//	}
//}


Matriz::Matriz(unsigned rows, unsigned cols)
{
	std::vector<float>m;
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
	std::vector<float>m;
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols, i * n);
	}

	this->rows = rows;
	this->cols = cols;
}

Matriz& Matriz::operator=(Matriz& other)
{
	rows = other.GetRows();
	cols = other.GetCols();
	Matriz temp(rows, cols);
	mat.resize(rows);
	for (int i = 0; i < mat.size(); i++)
	{
		mat[i].resize(cols);
		for (int j = 0; j < mat[i].size(); j++)
		{
			mat[i][j] = other(i, j);
			temp(i, j) = mat[i][j];
		}
	}
	return temp;
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