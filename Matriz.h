#pragma once
#include <vector>
#include "Vector2.h"

class Matriz
{
public:
	Matriz(unsigned rows, unsigned cols);
	Matriz(unsigned, unsigned, int);

	Matriz& operator=(Matriz&);
	Matriz operator+(Matriz&);
	/*
	Matriz operator-(Matriz&);
	Matriz operator* (Matriz&);
	void Transpose();

	Matriz operator+(float);
	Matriz operator-(float);
	Matriz operator* (float);*/

	float& operator()(unsigned, unsigned);
	unsigned GetRows();
	unsigned GetCols();
	void Print();

	~Matriz();

private:
	std::vector<std::vector<float>> mat;
	unsigned rows;
	unsigned cols;

};

