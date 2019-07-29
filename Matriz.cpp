#include "Matriz.h"
#include <iostream>

Matriz::Matriz(int x, int y) : sizeX(x), sizeY (y)
{
	m = new float* [x];
	for (int i = 0; i < x; i++)
	{
		m[x] = new float[y];
	}
	if (!m)
	{
		std::cout << "No se creo";
	}
	
	
}

void Matriz::PrintMatriz()
{
	for (int i = 0; i < sizeY; i++)
	{
		for (int j = 0; j < sizeX; j++)
		{
			std::cout<<m[j][i]<< " ";
		}
		std::cout << std::endl;
	}
}


Matriz::~Matriz()
{

}