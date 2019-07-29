#pragma once


class Matriz
{
public:
	Matriz(int x, int y);
	void PrintMatriz();
	~Matriz();

private:
	int sizeX;
	int sizeY;
	float** m;

};

