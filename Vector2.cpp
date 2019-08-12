#include "Vector2.h"
#include <iostream>

Vector2::Vector2()
{
	x = 0;
	y = 0;
	z = 1;
}

Vector2::Vector2(float x, float y) : x(x), y(y)
{
	z = 1;
}

void Vector2::Suma(float x, float y)
{
	this->x += x;
	this->x += y;
}

void Vector2::Resta(float x, float y)
{
	this->x -= x;
	this->x -= y;
}

Vector2 Vector2::operator +(Vector2 other)//Suma
{
	Vector2 temp;
	temp.SetX(this->x + other.GetX());
	temp.SetY(this->y + other.GetY());
	return temp;
}

Vector2 Vector2::operator -(Vector2 other)//Resta
{
	Vector2 temp;
	temp.SetX(this->x - other.GetX());
	temp.SetY(this->y - other.GetY());
	return temp;
}

float Vector2::operator *(Vector2 other)//Producto escalar
{
	int temp;
	temp = this->x * other.GetX();
	temp += this->y * other.GetY();
	return temp;
}

Vector2 Vector2::operator * (Matriz other)
{
	Vector2 temp;
	temp.SetX((x * other(0,0)) + (y * other(1,0)) + other(2,0));
	temp.SetY((x * other(0, 1)) + (y * other(1, 1)) + other(2, 1));
	return temp;
}

Vector2 Vector2::operator * (float num)//Producto por escalar
{
	Vector2 temp;
	temp.SetX(x * num);
	temp.SetY(y * num);
	return temp;
}

void Vector2::operator=(Vector2 other)
{
	x = other.GetX();
	y = other.GetY();
}

void Vector2::Draw(SDL_Renderer* gRenderer, int width, int height, int tam)
{
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
	float provx, provy;
	provx = (width / 2) + (tam * x);
	provy = (height / 2) - (tam * y);
	SDL_RenderDrawPoint(gRenderer, provx, provy);
}

void Vector2::SetX(float x)
{
	this->x = x;
}

void Vector2::SetY(float y)
{
	this->y = y;
}

float Vector2::GetX()
{
	return x;
}

float Vector2::GetY()
{
	return y;
}

void Vector2::Print()
{
	std::cout << "( " << x << ", " << y << ")" << std::endl;
}

Vector2::~Vector2()
{

}
