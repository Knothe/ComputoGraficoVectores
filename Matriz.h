#pragma once
#include <vector>


class Matriz
{
public:
	Matriz();
	Matriz(const Matriz& other);
	Matriz(unsigned rows, unsigned cols);
	Matriz(unsigned, unsigned, int);

	Matriz& operator=(Matriz);
	bool operator==(Matriz);
	Matriz& operator=(std::vector<std::vector<float>>);
	Matriz operator+(Matriz&);
	Matriz operator-(Matriz&);
	Matriz operator* (Matriz&);
	void Transpose();
	Matriz Inversa();
	
	Matriz operator+(float);
	Matriz operator-(float);
	Matriz operator* (float);

	float& operator()(unsigned, unsigned);
	unsigned GetRows();
	unsigned GetCols();
	void Print();

	~Matriz();

protected:
	std::vector<std::vector<float>> mat;
	unsigned rows;
	unsigned cols;


};

