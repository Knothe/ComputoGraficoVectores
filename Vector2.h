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
	int screenX;
	int screenY;
	int screenHeight;
	int screenWidth;
	int tam;
public:
	Vector2();
	Vector2(float x, float y);
	Vector2(float, float, int, int, int);

	void Suma(float x, float y);
	void Resta(float x, float y);
	void Draw(SDL_Renderer* gRenderer, int height, int width, int tam,int num);
	void Draw(SDL_Renderer* gRenderer);
	Vector2 operator * (Matriz other);
	Vector2 operator +(Vector2);//Suma
	Vector2 operator -(Vector2);//Resta
	float operator *(Vector2);//Producto punto
	Vector2 operator * (float);//Producto por escalar
	void operator=(Vector2);
	/*Vector2 operator * (Matriz);*/

	void SetX(float x);
	void SetY(float y);
	float GetX();
	float GetY();
	int GetScreenX() const;
	int GetScreenY() const;
	void Print();

	~Vector2();
};

