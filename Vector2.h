#pragma once
#include "Matriz.h"
#include <SDL.h>

class Vector2
{
private: 
	float x;
	float y;
	float z;
	float size = 0;
public:
	Vector2();
	Vector2(int x, int y);

	void Suma(int x, int y);
	void Resta(int x, int y);
	void Draw(SDL_Renderer* gRenderer, int height, int width, int tam);

	Vector2 operator +(Vector2);//Suma
	Vector2 operator -(Vector2);//Resta
	float operator *(Vector2);//Producto punto
	Vector2 operator * (float);//Producto por escalar
	void operator=(Vector2);
	/*Vector2 operator * (Matriz);*/

	void SetX(int x);
	void SetY(int y);
	float GetX();
	float GetY();
	void Print();

	~Vector2();
};

